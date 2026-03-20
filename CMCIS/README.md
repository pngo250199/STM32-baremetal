1. Introducing CMCIS
   - Think about an MCU chip is a complex apartment where it has blue sprint including kitchen, bedroom, living room. Each section has it locations and setup and developer could base on that to setting up for which section and modify it

2. Structures
   - for STM32F4
```// 1: GPIO_TypeDef structure definition
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

} RCC_TypeDef;```
