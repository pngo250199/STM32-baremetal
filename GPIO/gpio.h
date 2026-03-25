/*
 * gpio.h
 *
 *  Created on: Feb 7, 2026
 *      Author: Henry
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "stm32f1xx.h"

void led_init(void);

void led_on(void);


void led_off(void);
void led_toggle(void);

#endif /* GPIO_H_ */
