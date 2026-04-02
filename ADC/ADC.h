/*
 * ADC.h
 *
 *  Created on: Feb 26, 2026
 *      Author: Henry
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void adc_init (void);
uint32_t adc_read(void);
void adc_start_conversation(void);
//uint32_t adc_wait_for_finish_reading();


#endif /* ADC_H_ */
