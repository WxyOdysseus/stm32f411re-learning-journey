#include "stm32f4xx.h"
#include <stdint.h>
/*aim: light up a LED*/
/*where: PA5 (pin 21)*/
/*what PA5 connected to: AHB1*/

#define RCC_GPIOAEN_C			(1U<<0)/*C means configure*/
#define GPIOA_MODER_C_TO_O      (1U<<10)/*O means output mode, should not change other configuration*/
#define GPIOA_BSRR_P5_S			(1u<<5)/*GPIOA BSRR pin5 set */

int main(void)
{
	/******Enable RCC->AHB1EN********/
	RCC->AHB1ENR |= RCC_GPIOAEN_C;
	/******configure PA5*********/

	/*set GPIOA->MODER*/
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER &= ~(1U<<11);/*based on the page 153 UM*/
	GPIOA->MODER |= GPIOA_MODER_C_TO_O;


	while(1)
	{
		/*set GPIOA->BSRR*/
		GPIOA->BSRR |= GPIOA_BSRR_P5_S;

	}


}
