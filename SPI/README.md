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
    GPIOA -> MODER &= ~((1U << 10) | (1U << 12) | (1U << 14)); //clear bit for PA5 6 and 7
    GPIOA -> MODER |= ((1U << 11) | (1U << 13) | (1U << 15)); //set bit for PA5 6 and 7

    
    //set PA9 for output
    GPIOA -> MODER &= (1U << 19);
    GPIOA -> MODER |= (1U << 18);
    
    
    //bit 0 to 7 using AFR 0 
    GPIOA -> AFR[0] |= ((1U << 20) | (1U << 22) | (1U << 24) | (1U << 26) | (1U << 28));
    GPIOA -> AFR[0] &= ~((1U << 21) | (1U << 23) | (1U << 25) | (1U << 27) | (1U << 31));
```
- In configuration function, developer will setting up specific for the slave that going to use. In this function there are four critical things need to be setting up are Clock Polarity (CPOL), Master/Slave declaration, Clock Speed (prescals), and Clock Phase (CPHA). 
 - Start with CPOL (Clock Polarity), short explaination is the default or inactive state of a signal
   	- CPOL = 0 -> clock idle LOW
   	- CPOL = 1 -> clock idle HIGH
   	- The purpose of CPOL (Clock Polarity) is to define the idle state of the clock line (SCK) in a synchronous serial interface like SPI. It ensures that both the Master and the Slave agree on what the signal looks like when no data is being moved. Without a defined CPOL, the receiver wouldn't know if the first voltage transition it sees is the start of a bit or just electrical noise.
	
