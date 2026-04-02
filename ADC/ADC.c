/*
 * ADC.c
 *
 *  Created on: Feb 26, 2026
 *      Author: Henry
 */

#include "ADC.h"
#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOAEN (0x1 << 0)
#define ADC1EN (0x1 << 8)
#define ADC_CHANNEL1 1 << 0
#define ADC_SEQ 0x00
#define CHANNEL_REGISTER2_ADC_ON (0x1 << 0)
#define CHANNEL_REGISTER2_CONTINUE (0x1 << 1)
#define CHANNEL_START (0x1 <<30)
#define SR_END_OF_CONVO (0x1 <<1)


void adc_init(void)
{
	RCC -> AHB1ENR |= GPIOAEN; //enable clock GPIO
	GPIOA -> MODER &= ~(0xf << 2);
	GPIOA -> MODER |= (0x3 << 2); //11 for bit 2 and 3 -> 11 -> analog mode
	RCC -> APB2ENR |= ADC1EN; // enable clock for ADC
	ADC1-> SQR3 = ADC_CHANNEL1; // SQR -> sequence register
	ADC1 -> SQR1 = ADC_SEQ; //to help the code understand there still have conversions, (L = number of conversions -1) -> if have more than 1 conversions (for example 3) it will be L = 3 - 1 -> SQR1 = (3 - 1 <<20);
	ADC1 -> CR2 |= CHANNEL_REGISTER2_ADC_ON; //enable ADC
	//systick_delay(1000); //delay
}

void adc_start_conversation(void)
{
    // 1. enable continious convo
    ADC1 -> CR2 |= CHANNEL_REGISTER2_CONTINUE;

    //start ADC conversinm
    ADC1 -> CR2 |= CHANNEL_START;
}

uint32_t adc_read(void)
{


    // 2. Wait for the "End of Conversion" (EOC) flag in the Status Register
    while (!(ADC1 -> SR & SR_END_OF_CONVO)){}

    // 3. Return the result from the Data Register
    return (ADC1 -> DR);
}

uint32_t adc_wait_for_finish_reading(void)
{
	while (!(ADC1 -> SR & SR_END_OF_CONVO)){}
	return (ADC1 -> DR);
}
