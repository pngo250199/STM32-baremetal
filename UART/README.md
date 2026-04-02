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
