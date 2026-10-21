

#include "stm32f4xx.h"
#include "led.h"

/*where:
 * the green LED is a user LED connected to ARDUINO® signal D13 corresponding
to STM32 I/O PA5 (pin 21) or PB13 (pin 34) depending on the STM32 target. */

/*port A is connected to AHB1*/

/*When the pin is configured as output, the value written to the output data register
(GPIOx_ODR) is output on the I/O pin. It is possible to use the output driver in push-pull
mode or open-drain mode (only the N-MOS is activated when 0 is output).
The input data register (GPIOx_IDR) captures the data present on the I/O pin at every AHB
clock cycle.
All GPIO pins have weak internal pull-up and pull-down resistors, which can be activated or
not depending on the value in the GPIOx_PUPDR register.*/

void led_init(void)
{
	/*enable clock access to AHB1->GPIOA*/
	RCC->AHB1ENR |=(1U<<0);
	/*set GPIO pin5 mode to out put mode */
	GPIOA->MODER &= ~(3U<<10);
	GPIOA->MODER |= (1U<<10);
	/*output type */
	GPIOA->OTYPER &= ~(1U << 5);   // 推挽输出
	/*output speed */
	GPIOA->OSPEEDR &=~(3U<<10);
	GPIOA->OSPEEDR |=(1U<<10);//medium speed

}


void led_active(void)
{

	GPIOA->BSRR |=(1U<<5);
}

void led_diminish(void)
{
	GPIOA->BSRR |= (1U<<(21));
}
