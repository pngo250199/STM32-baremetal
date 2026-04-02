
// 0: Include standard integer types header for fixed-width integer types
#include <stdint.h>

// 1: GPIO_TypeDef structure definition
typedef struct
{
  volatile uint32_t MODER;    /*offset: 0x00  Mode Register (MODER)    */
  volatile uint32_t OTYPER;   /*offset: 0x04  Output Type Register (OTYPER)    */
  volatile uint32_t OSPEEDR;  /*offset: 0x08  Output Speed Register (OSPEEDR)    */
  volatile uint32_t PUPDR;    /*offset: 0x0C  Pull Up/Pull Down Register (PUPDR)    */
  volatile uint32_t IDR;      /*offset: 0x10  Input Data Register (IDR)    */
  volatile uint32_t ODR;      /*offset: 0x14  Output Data Register (ODR)    */
  volatile uint32_t BSRR;     /*offset: 0x18  Bit Set/Reset Register (BSRR)    */
  volatile uint32_t LCKR;     /*offset: 0x1C      */
  volatile uint32_t AFRL;     /*offset: 0x20	 */
  volatile uint32_t AFRH;     /*offset: 0x24 	 */

} GPIO_TypeDef;

// 2: RCC_TypeDef structure definition
typedef struct
{
  volatile uint32_t DUMMY[12];
  volatile uint32_t AHB1ENR;       /*offset: 0x30*/

} RCC_TypeDef;


// 3: Base address definitions
#define 	RCC_BASE	 0x40023800
#define 	GPIOA_BASE   0x40020000

// 4: Peripheral pointer definitions
#define RCC		    ((RCC_TypeDef*) RCC_BASE)
#define GPIOA		((GPIO_TypeDef*)GPIOA_BASE)

//5: Bit mask for enabling GPIOA (bit 0)
#define GPIOAEN       (1U<<0)
//6: Bit mask for GPIOA pin 5
#define PIN1          (1U<<1)
//7: Alias for PIN5 representing LED pin
#define LED_PIN1       PIN1

#define PIN5          (1U<<5)
//7: Alias for PIN5 representing LED pin
#define LED_PIN5      PIN5
//  8: Start of main function
int main(void)
{

	uart_init();
	for (volatile int i = 0; i < 100; i++);
    //  9: Enable clock access to GPIOA
	// RCC->AHB1ENR |=  GPIOAEN;

	// GPIOA->MODER &= ~(11U<<10); //  11: Set bit 11 to 0
	// GPIOA->MODER |= (1U<<10);  //  10: Set bit 10 to 1

	 //GPIOA->MODER &= ~(3U<<2); //  3: Set bit 3 to 2
	 //GPIOA->MODER |= (1U<<2);  //  2: Set bit 2 to 1


    //  21: Start of infinite loop
    //while(1)
    //{
    	//  12: Set PA5(LED_PIN) high
	//	GPIOA->ODR^= LED_PIN5;

        // 13: Simple delay
	//	for(volatile uint32_t i=0;i<100000;i++){}

    	//  12: Set PA5(LED_PIN) high
	//	GPIOA->ODR^= LED_PIN1;

        // 13: Simple delay
	//	for(volatile uint32_t i=0;i<100000;i++){}

    //}

	while(1)
	{
		uart_print("testing...\r\n");

		//char c = uart_receive();
		//uart_transmit(c);
		for (volatile int i = 0; i < 100; i++);


	}

}




/*
int sensor_value;
int main(void)
{

	uart_init();
	adc_init();
	adc_start_conversation();
	//adc_init();
	//adc_read();
    //  9: Enable clock access to GPIOA
	// RCC->AHB1ENR |=  GPIOAEN;

	// GPIOA->MODER &= ~(11U<<10); //  11: Set bit 11 to 0
	// GPIOA->MODER |= (1U<<10);  //  10: Set bit 10 to 1

	 //GPIOA->MODER &= ~(3U<<2); //  3: Set bit 3 to 2
	 //GPIOA->MODER |= (1U<<2);  //  2: Set bit 2 to 1


    //  21: Start of infinite loop
    //while(1)
    //{
    	//  12: Set PA5(LED_PIN) high
	//	GPIOA->ODR^= LED_PIN5;

        // 13: Simple delay
	//	for(volatile uint32_t i=0;i<100000;i++){}

    	//  12: Set PA5(LED_PIN) high
	//	GPIOA->ODR^= LED_PIN1;

        // 13: Simple delay
	//	for(volatile uint32_t i=0;i<100000;i++){}

    //}

	/*while(1)
	{
		//uart_print("testing...\r\n");

		//char c = uart_receive();
		//uart_transmit(c);
		//for (volatile int i = 0; i < 10; i++);


		sensor_value = adc_read();
		printf("Value: %d\r\n", sensor_value);
	}

	while(1)
	{
	    uart_print("HELLO\r\n");

	    for (volatile int i = 0; i < 100000; i++);
	}
}

*/
