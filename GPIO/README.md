1. Understanding GPIO peripheral
  Microcontroller pins are grouped into ports. For instance, a microcontroller might have ports named GPIOA, GPIOB, and GPIOC. Each port is composed of individual pins, which are referred to by their port name, followed by their pin number.

2. GPIO in STM32F4
   STM32F4 has SIX ports are portA, portB, portC, portD, portD, and portH. Each port is equipped with a comprehensive set of registers to manage configuration, data handling and functionality
   Features offered including the following
   - I/O control: allow to manage up to 16 I/O pins per port
   - Output states: Pins can be configured for push-pull or open-drain modes, with optional pull-up or pull-down resistors
   - Output data: Output data is driven by the GPIOx_ODR register when the pin is configured as a general-purpose output. For alternate function configurations, the associated peripheral drives the output data
   - Speed selection
   - Input states
   - Inpuut data
   - Configuration locking
   - Alternate function selection
  
3.GPIO registers
   - GPIOx_MODER (mode register)
   - GPIOx_OTYPER (output type register)
   - GPIOx_OSPEEDR (output speed register)
   - GPIOx_PUPDR (pull up/pull down register)
   - GPIOx_IDR (input data register)
   - GPIOx_ODR (output data register)
NOTE: GPIOx_BSRR (bit set/reset register) and GPIOx_LCKR (locking register) are used to control pin states and access. Additionally, the alternate function selection registers, GPIOx_AFRH and GPIOx_AFRL, manage the alternate function assignments for the pins within the GPIO port.

- For mode registers of GPIO in CMSIS
    - struct of GPIO registers
    - struct of RCC register
    - To active any pin -> clear and write method
    - To get output, us BSRR or ODR (*ODR toggle is x(^=) )
*NOTE: Each pin has 2 bits, to apply clear and write method from any pin
  ```
  pin &= ~(0x3 << (pin number *2); // *2 because the F4 using 2 bits and 0x3 is 11 in binary
  pin |= (mode << (pin number * 2); modes are 00, 01, 10, and 11
  ```
For example choosing pin PA5 (bit 11:10):
  - 0x3 = 0011 -> clear at bit 10 -> 0000
  - 0x1 = 0001 -> write at bit 10 -> 0001 (01 is output mode -> using port PA5 to output data)


For STM32F1 blue pill
  - developer not using MODER or ODR, instead that developer usr CRL (configuration register low) and CRH (configurations register high)
  *NOTE: CRL using for pins 0-7 and CRH using for pins 8-15. 8 pins of CRL will start with 0 while 8 pins of CRH will start with 1.
  Code register example for any pins of CRL from 0-7 
```
  pin &= ~(0xF << (pin number *4); // *4 because the F1 using 4 bits and 0xF is 1111 in binary
  pin |= (mode << (pin number * 4); modes are 00, 01, 10, and 11
```
  Code register example for any pins of CRH from 8-15
```
  pin &= ~(0xF << ((pin number - 8) *4)); // *4 because the F1 using 4 bits and 0xF is 1111 in binary
  pin |= (mode << ((pin number - 8) * 4)); modes are 00, 01, 10, and 11
```
