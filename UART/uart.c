/*
 * uart.c
 *
 *  Created on: Feb 11, 2026
 *      Author: Henry


#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN (1U << 0)
#define UART1EN (1U << 4)

#define rate 115200
#define sys_freq 16000000
#define APB2_CLK sys_freq
#define CR_TE (1U << 3)
#define CR_RE (1U << 2)
#define CR1_UE (1U << 13)
#define SR_TXE (1U << 7) //transmit
#define SR_Receive (1U << 5)
#define TX (1U << 9)
#define RX (1U << 10)

void uart_init(int ch)
{
	RCC -> APB2ENR |= GPIOAEN; // enable clock for GPIO A
	RCC -> APB2ENR |= UART1EN; // enable clock for UART 1

	//TX in pin A2
	 GPIOA->MODER &= ~(0x3<<(9 *2));
	 GPIOA->MODER |= (0x2<<9* 2);

	//RX in pin A3
	 GPIOA->MODER &= ~(0x3<<(10*2));
	 GPIOA->MODER |= (0x2<<(10*2));

	USART1 -> BRR = 0x8A; //config baurate register (BRR) = APB2_Clock/rate = 16000000/115200 = 69.44, 69 is 45 in hex
	USART1 -> CR1 = CR_TE |CR_RE | CR1_UE; // config transfer direction and enable UART for TE, RE and UE

	//set AFR
	GPIOA -> AFR[1] &= ~(0xF <<4);
	GPIOA -> AFR[1] |= (0x7 << 4);

	GPIOA -> AFR[1] &= ~(0xF << 8);
	GPIOA -> AFR[1] |= (0x7 << 8);
}


void uart_transmit(char data)
{
	while (!(USART1 ->  SR &  SR_TXE)){} //check transmit data is empty, this time SR_TXE is !0 -> 1 cannot send yet

	USART1 -> DR = (data & 0xFF);
}

uart_receive(char data)
{
	while (!(USART1 -> SR & SR_Receive)){}

	return USART1 -> DR;
}

int __io_putchar(int data)
{
	uart_transmit(data);
	return data;
}

 */


#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOAEN   (1U << 0)
#define USART2EN  (1U << 17)

#define CR_TE     (1U << 3)
#define CR_RE     (1U << 2)
#define CR1_UE    (1U << 13)
#define SR_TXE    (1U << 7)
#define SR_RXNE   (1U << 5)

#define sys_freq 16000000
#define rate     115200

void uart_init(void)
{
    // Enable clocks
    RCC->AHB1ENR |= GPIOAEN;      // GPIOA
    RCC->APB1ENR |= USART2EN;     // USART2

    // PA2 and PA3 alternate function
    GPIOA->MODER &= ~(0x3 << (2*2));
    GPIOA->MODER |=  (0x2 << (2*2));
    GPIOA->MODER &= ~(0x3 << (3*2));
    GPIOA->MODER |=  (0x2 << (3*2));

    // AF7 for USART2
    GPIOA->AFR[0] &= ~(0xFF << (4*2));
    GPIOA->AFR[0] |=  (0x77 << (4*2));

    // Baud rate
    USART2->BRR = sys_freq / rate;

    // Enable TX, RX and USART
    USART2->CR1 = CR_TE | CR_RE | CR1_UE;
}

void uart_transmit(char data)
{
    while (!(USART2->SR & SR_TXE)){}
    USART2->DR = data;
}

char uart_receive(void)
{
	while (!(USART2 -> SR & SR_RXNE)){}

	return (char)(USART2 -> DR);
}

void uart_print(char *str)
{
    while (*str)
    {
        uart_transmit(*str++);
    }
}
