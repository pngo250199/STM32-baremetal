1. Introducing CMCIS
   - Think about an MCU chip is a complex apartment where it has blue sprint including kitchen, bedroom, living room. Each section has it locations and setup and developer could base on that to setting up for which section and modify it
2. Initial CMSIS
   - Download STM32F4/F1 package then unzip the file
   - Locate stm32f4 package file and looking for Driver
   - Locate the project file, create new folder named chip_header
   - Create folder named CMSIS
   - Next, copy entire Include and Device from Drivers of stm32f4/f1 package into chip_headers/CMSIS
   - Navigate chip_headers/CMSIS/Device/ST/STM32F4xx then delete all files and folder, except the Include filder -> ensures keep only the necessary header files for specific micrcontroller
   - Open STM32CubeIDE, right click on the project and select properties
   - In properties window, expand the C/C++ General options then select Paths and Symbols
   - Under the Includes tab, clock Add to add a new directory to add both Include and STM32F4xx/Include from just created in project file
    <img width="1191" height="611" alt="image" src="https://github.com/user-attachments/assets/5582e8c7-531b-44d0-bcea-c408cc393e41" />
   - The last step is specify the exact version of the STM32F4/F1 microcontroller gonna use by click the # symbol
   - In # symbol tab, click add then enter STM32F32F411xE in the Name field then click OK, for F1 will be STM32F103xB
   - <img width="1052" height="611" alt="image" src="https://github.com/user-attachments/assets/fb2717b9-55c5-4605-ad48-a3f862204026" />


4. Structures
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
```
The line typedef struct begins the definition of a new structure type. Typedef is used to create an alias for the structure, allowing us to use GPIO_TypeDef as a type name later in the code

   - volatile: indicates that the value of the variables can be changed anytime
   - uint32_t: usign initial 32 bit
   - MODER: mode Register (since STM32F4 series using 2 bits only, we have 4 modes 00, 01, 10 and 11 in order are input mode, output mode, alternate function mode, and Analog mode)
     
```
// 2: RCC_TypeDef structure definition
typedef struct
{
  volatile uint32_t DUMMY[12];
  volatile uint32_t AHB1ENR;       /*offset: 0x30*/

} RCC_TypeDef;
```
The RCC has about 24 registers, in this tpye, its added padding to the structure with the number of uint32_t (4 bytes) itmes required to reach the offset 0x30. In this case, it is 12 itmes. This is because 4 bytes multiplied by 12 = 48 bytes, which corresponds to 0x30 in hex




