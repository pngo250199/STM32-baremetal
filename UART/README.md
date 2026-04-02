1. Understanding UART
   - UART (Universal Asynchronous Receiver/Transmiter) is a hardware peripheral used for serial commuinication between devices
   - Asynchronous -> no share clock line
   - Uses only for TX (transmit) and RX (Receive)

2. How UART functioning
   - With Four stages
      - Start bit -> signals beginning (usually LOW)
      - Data bits -> typically 8 bits
      - parity -> error checking (optinal)
      - stop bit(s) -> end of frame (HIGH)
   - Conditionals both devices must:
      - Running on the same rate (9600, 115200) if not will get trash datas
          - Baud rate can be calculate by:  APB2_Clock/rate = 16000000/115200 = 69.44, 69 is 45 in hex
            
      ```
      USART1 -> BRR = 0x8A; //config baurate register (BRR) = APB2_Clock/rate = 16000000/115200 = 138, 138 is 8A in hex
     ```
      
      - Data length
      - Parity
      - Stop bits
    
   3. How functions of UART works
      - In STM32F4x series, UART using PA2 and 3 in order for transmit and receive. Same with GPIO, uart need to enable its RCC at AHB1
   ```
          RCC->AHB1ENR |= GPIOAEN;
    RCC->APB1ENR |= USART2EN;

    // PA2 (TX), PA3 (RX) → AF mode
    GPIOA->MODER &= ~(0xF << (2 * 2));
    GPIOA->MODER |=  (0xA << (2 * 2));
   ```
      - The next step is declare Altenate function, AF in uart setting for specific pins that telling hardware thta those pins no simply I/O pins any longer. Instead that, those specific pins serve as TX and RX pins
  
   ```
       // AF7 (USART2)
    GPIOA->AFR[0] &= ~(0xFF << 8);
    GPIOA->AFR[0] |=  (0x77 << 8);
   ```
AFR[0] for pins 0 to 7
AFR[1] for pins 8 to 15
In this case we use PA2 and 3 so AFR[0]



4. Initial receive and transmit functions
```
   void uart_transmit(char data) //sending input out from MUC
{
    while (!(USART2->SR & SR_TXE)){}
    USART2->DR = data;
}

char uart_receive(void) //receive input from others
{
	while (!(USART2 -> SR & SR_RXNE)){}

	return (char)(USART2 -> DR);
}
```



```
void uart_print(char *str)
{
    while (*str)
    {
        uart_transmit(*str++);
    }
}
  ```
*NOTE: unlike C++, string not sprint whole paragrapth, so we using the loop while for spring every single charater 
for example in main we want to print "testing...", with str++ that will print letter by letter until finish whole paragraph.

*NOTE: For this topic, developer should careful in baud rate and system rate. if different baud rate, MCUs cannot communicate in the same speed will give garbage data. For system rate, if calculating wrong even a small value, the board would read too fast and miscommunication still giving garbage data, however for this one could temperary solve by debugging with gdb since gdb go step by step that make the timer slow and match with the communication speed that make the data stable.
