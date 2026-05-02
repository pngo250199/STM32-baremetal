1. Understanding SPI
   - SPI main functions are ONE master sending data and control for one or more than one slaves, each slave have a unique address and giving an output. Most of cases using SPI are using sensors, LCD or memory flask.
   - SPI has main four wires - Clock, Master In Slave Out (MISO), Master Out Slave In (MOSI), and Chip Select (CS)
   - In SPI (Serial Peripheral Interface) communication, the timing of when data is driven onto the MOSI (Master Out Slave In) and MISO (Master In Slave Out) lines is determined by the Clock Phase (CPHA) and Clock Polarity (CPOL) settings.

*NOTE:When you refer to transmitting or sampling in the "middle" of a clock cycle, you are likely looking at CPHA=1.
   - A single SPI clock cycle consists of two edges: a leading edge and a trailing edge.

		CPHA=0: Data is sampled on the leading edge and shifted out (changed) on the trailing edge.

		CPHA=1: Data is shifted out on the leading edge and sampled on the trailing edge (the "middle" or end of the pulse).

2. Configuration for SPI
   - Developer usually need to setting up for slaves first before setting up clock execute from master
   - In embedded, developers going to separate initial and config into two different functions. Initial will setting up basic clock, SPI mode for GPIO and config will setting up for type of transmition for master and slave
  
```
void SPI_init(void)
{
	//RCC for GPIOA
    RCC->AHB1ENR |= GPIOAEN;
    //RCC for SPI1
   // RCC->APB2ENR |= SPI1EN;
    
    
    //set PA5 6 and 7 for alternate function pins
    GPIOA -> MODER &= ~((3U << 10) | (3U << 12) | (3U << 14)); //clear bit for PA5 6 and 7
    GPIOA -> MODER |= ((1U << 10) | (1U << 12) | (1U << 14)); //set bit for PA5 6 and 7

    
    //set PA9 for output
    GPIOA -> MODER &= (1U << 18);
    GPIOA -> MODER |= (2U << 18);
    
    
    //bit 0 to 7 using AFR 0 
    GPIOA -> AFR[0] |= ((1U << 20) | (1U << 22) | (1U << 24) | (1U << 26) | (1U << 28)); 
    GPIOA -> AFR[0] &= ~((1U << 21) | (1U << 23) | (1U << 25) | (1U << 27) | (1U << 31));
```
- For SPI, after setting pins are altenate function, developer will need to setup the AFR for GPIO pins that going to use for altenate function. In STM32f4, this is important when using AF pins because the f4 is more flexible and one pin can use in many functions that need extra step, while stm32f1 chip not that flexible so when developer would like to use altenate functions pin just only need to active and dont need to setting up register like F4
- Structure to write down AF register is
```
GPIOx -> AFR[0 or 1] &= ~(0xF << (pin* 4));
GPIOx -> AFR[0 or 1] |= (AF mode number << (pin *4));
```
NOTE: 0 for pin 0 to 7 and 1 for pin 8 to 15. There are 8 AFR mode 
<img width="737" height="327" alt="Screenshot From 2026-05-02 14-01-37" src="https://github.com/user-attachments/assets/de86edfb-f6a2-4390-884b-81b9e80120e0" />

for this style:
```
GPIOA -> AFR[0] |= ((1U << 20) | (1U << 22) | (1U << 24) | (1U << 26) | (1U << 28));
GPIOA -> AFR[0] &= ~((1U << 21) | (1U << 23) | (1U << 25) | (1U << 27) | (1U << 31));
```
The logic is set each bit to become AF number mode, for example 5 is 0101, pin A is bit [23:20] so when clear and write we have
- bit 20: 1
- bit 21: 0
- bit 22: 1
- bit 23: 0
Same logic with pin 6 and 7, however this style make it slow and only for teaching to show how the SPI pins works

- In configuration function, developer will setting up specific for the slave that going to use. In this function there are four critical things need to be setting up are Clock Polarity (CPOL), Master/Slave declaration, Clock Speed (prescals), and Clock Phase (CPHA). 
 - Start with CPOL (Clock Polarity), short explaination is the default or inactive state of a signal
   	- CPOL = 0 -> clock idle LOW
   	- CPOL = 1 -> clock idle HIGH
   	- The purpose of CPOL (Clock Polarity) is to define the idle state of the clock line (SCK) in a synchronous serial interface like SPI. It ensures that both the Master and the Slave agree on what the signal looks like when no data is being moved. Without a defined CPOL, the receiver wouldn't know if the first voltage transition it sees is the start of a bit or just electrical noise.
   	- Developer active bit by this map
	<img width="862" height="777" alt="image" src="https://github.com/user-attachments/assets/82927639-e687-4a00-bde5-6793bccdb037" />

*NOTE: For the BR[2:0], Look at the table for bits [5:3] BR[2:0]. You will see a list of dividers:

000: fPCLK/2

001: fPCLK/4 (This is what your code is setting)

010: fPCLK/8

...and so on.

```
    SPI1 -> CR1 |= (1U << 3);
    SPI1 -> CR1 &= ~(1U << 4);
    SPI1 -> CR1 &= ~(1U << 5);
```

	
