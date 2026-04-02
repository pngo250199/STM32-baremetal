/*
 * uart.h
 *
 *  Created on: Feb 11, 2026
 *      Author: Henry
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart_init(void);
void uart_transmit(char data);
uart_receive(char data);


//int __io_putchar(int data);
#endif /* UART_H_ */
