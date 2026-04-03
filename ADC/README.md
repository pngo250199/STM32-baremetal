1. Overview of analog-to-digital conversion
   - ADC is the process of converting a continous analog signal into a discrete digital representation. Analog signals, which can have any value within a certain range, are transformed into digital signals, which have specific, quantized levels. This conversion is essential because MCU and digital system can only process digital data
   - Sampling: involves measuring the amplituded of an analog signal at regular intervals, called sampling intervals. The result is a series of discrete value that approximate the original analog.
   - Quantization: the process of mapping the sampled analog values to the nearest discrete levels available in the digital domain. Each discrete level corresponds to a unique digital code. The number of discrete level available for quantization is determined by the resolution of the analog-to-digital converter.
   - Encoding is the final step and is where the quantized levels are converted into a binary code that can be processed by the digital system. Each quantized level is represented by a unique binary value.
   - In short, the ADC process with an analog input signal, which can vary continuously over time. This signal could be a voltage from a temperature sensor, and audio signal, or any other analog signal.Th ADCconverter typically includes a sample-and-hold circuit that captures and holds the analog signal at each sampling interval. This ensures that the signal remains constant during the conversion process. The core of the ADC performs quantization and encoding. It compares the held analog value to a set of reference voltage to determine the closet matching digital level

2. Developing ADC
   - As usual, enable clock with RCC for ADC, GPIO, in this time gonna use PA1
   - As mentioned in GPIO session, developer must config the mode for any pins going to use, in this session gonna put PA1 into analog mode which mean 11

```
    RCC->AHB1ENR |= GPIOAEN;

    // ONLY configure PA1
    GPIOA->MODER &= ~(0x3 << 2);
    GPIOA->MODER |=  (0x3 << 2);

    RCC->APB2ENR |= ADC1EN;
```

   - The next step when inital for ADC is developer choose the channel
```
    ADC1->SQR3 = 1;        // channel 1
    ADC1->SQR1 = 0;
```
   *NOTE 1: Sequence Register (SQR) in ADC take the important role in this concept. Developer could convert multiple channel in a specific order, for example SQR1 -> 3 -> 5..., and then we declare the total number of conversions by formula L + 1. In this case we declare ADC1 -> SQR1 = 0; -> 0 + 1 = 1 conversion only
   *NOTE 2: When developing ADC, the sequence register expect for exact number instead of bit mask. 
   *NOTE 3: For declaring the total number of conversion, the L number exist ONLY in SRQ1, and in bit 20 in specific. In this example we only use single channel, thinking like 0 << 20 = 0 so we dont really need to shifting for this example. For developing more than one channel, the number of conversion will be follow by 
   ```
   #define ADC_SQR_L_POS 20
   ADC1 -> SQR1 = ((Number of conversion - 1) << ADC_SQR_L_POS);
   ```
``` 
   Conversion order	Register location
1st conversion	SQR3
2nd–6th	SQR3
7th–12th	SQR2
13th–16th	SQR1
```

   - To wrap this concept, Sequence Register (SQR) following three importants things:
      - Channel
      - Number of conversions
      - Sequence number need to use
   - For channel and which pins to use, developers could follow this table
```
Channel	Pin	GPIO Port
0	      PA0	GPIOA
1	      PA1	GPIOA
2	      PA2	GPIOA
3	      PA3	GPIOA
4	      PA4	GPIOA
5	      PA5	GPIOA
6	      PA6	GPIOA
7	      PA7	GPIOA
8	      PB0	GPIOB
9	      PB1	GPIOB
10	      PC0	GPIOC
11	      PC1	GPIOC
12	      PC2	GPIOC
13	      PC3	GPIOC
14	      PC4	GPIOC
15	      PC5	GPIOC
```

```
Conversion #	Register	Bits
1 (SQ1)	      SQR3	   [4:0]
2 (SQ2)	      SQR3	   [9:5]
3 (SQ3)	      SQR3	   [14:10]
4 (SQ4)	      SQR3	   [19:15]
5 (SQ5)	      SQR3	   [24:20]
6 (SQ6)	      SQR3	   [29:25]
7 (SQ7)	      SQR2	   [4:0]
8 (SQ8)	      SQR2	   [9:5]
9 (SQ9)	      SQR2	   [14:10]
10 (SQ10)	   SQR2	   [19:15]
11 (SQ11)	   SQR2	   [24:20]
12 (SQ12)	   SQR2	   [29:25]
13 (SQ13)	   SQR1	   [4:0]
14 (SQ14)	   SQR1	   [9:5]
15 (SQ15)	   SQR1	   [14:10]
16 (SQ16)	   SQR1	   [19:15]
```
*IMPORTANT: Developer select channel number in SQR must configure the matching GPIO pin to analog mode

Example: Developer want to read 3 channels 1, 8 and 12
-> total 3 conversion (L = 2), pins going to use in order by PA1, PB0 and PC2
-> to declaration SQR, with channel 1, 8 and 12, follow the conversion number register table and the bits location we shift channel by order 1 << 0, 8 <<5 and 12 << 10.
Sequence can be follow by formula: channel << (5* (sequence_position -1))
```
#define sequence_position_1 1
#define sequence_position_2 3
#define sequence_position_3 3
#define channel_1 1
#define channel_8 8
#define channel_12 12

//sequence
ADC1 -> SQR3 = channel_1 << (5* (sequence_position_1 -1)) | channel_8 << (5* (sequence_position_2 -1)) | channel_12 << (5* (sequence_position_3 -1));
//lenght
ADC1 -> SQR1 = (2 << 20);

```
