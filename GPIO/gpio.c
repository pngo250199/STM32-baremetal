
#include "stm32f1xx.h"
#include "gpio.h"
#define GPIOAEN	(1U <<2)
#define GPIOCEN (1U <<4)
#define PIN5	(1U << 5)
#define LED_PIN5 PIN5
#define PIN13 (1U << 13)
#define LED_PIN13 PIN13

void led_init(void)
{

	RCC -> APB2ENR |= GPIOAEN;
	RCC -> APB2ENR |= GPIOCEN;

	//config and mode for pin PA5 0010
	GPIOA -> CRL &= ~(0xF << (5 *4));
	GPIOA -> CRL |=  (0x2 << (5* 4));

	//config and mode for Pin PA1
	GPIOA -> CRL &= ~(0xF << (1 * 4));
	GPIOA -> CRL |= (0x2 << (1 * 4));

	GPIOC -> CRH &= ~(0xF << ((13-8) *4));
	GPIOC -> CRH |= (0x2 << ((13-8)*4));

	//GPIOA -> ODR &= ~(LED_PIN1 | LED_PIN5);
	GPIOC -> ODR |= LED_PIN13;

}

void led_on(void)
{
	GPIOA -> BSRR = LED_PIN5;
	GPIOC -> BSRR = (LED_PIN13 << 16);
}

void led_off(void)
{
	GPIOA -> BSRR = (LED_PIN5 << 16);
	GPIOC -> BSRR = LED_PIN13;

}

void led_toggle(void)
{
	GPIOA -> ODR ^= LED_PIN5;
	GPIOC -> ODR ^= LED_PIN13;
}

