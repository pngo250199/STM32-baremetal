1. Understanding SPI
   - SPI main functions are ONE master sending data and control for one or more than one slaves, each slave have a unique address and giving an output. Most of cases using SPI are using sensors, LCD or memory flask.

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
