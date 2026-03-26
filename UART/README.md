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
