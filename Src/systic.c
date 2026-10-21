
#include "stm32f4xx.h"//其实一点用处都没有
#include<stdint.h>
#include "systic.h"

#define SYST_CSR			(*(volatile uint32_t *)(0xE000E010))
#define SYST_RVR			(*(volatile uint32_t *)(0xE000E014))
#define SYST_CVR			(*(volatile uint32_t *)(0xE000E018))
#define SYST_CALIB		(*(volatile uint32_t *)(0xE000E01C))


/*The SysTick calibration value is fixed to 16000, which gives a reference time base of 1 ms
with the SysTick clock set to 16 MHz */

/*1.
Program reload value.
2.
Clear current value.
3.
Program Control and Status register.*/

void  systic_delay_ms(uint32_t delay, uint32_t clk_freq)
{
	/*Program reload value.*/
	SYST_RVR=(clk_freq/1000)-1;//低于1khz的老古董不可以使用
	/* For example, to generate a multi-shot
	timer with a period of N processor clock cycles, use a RELOAD value of N-1. If the SysTick
	interrupt is required every 100 clock pulses, set RELOAD to 99.*/


	/*clear current value*/
	 SYST_CVR=0;
	 /**program Control and Status register**/
	 /*select clock source*/
	 SYST_CSR |=(1U<<2);
	/*enable systic timer*/
	SYST_CSR |= (1U<<0);

	/**/
	for(volatile uint32_t i=0;i<delay;i++)
	{
		while(!(SYST_CSR &(1U<<16))){} /*systic_unit 是systic_delay_ms的附属函数 提供单位1ms,当正好1ms的时候 返回1*/

	}

	SYST_CSR &= ~(1U<<0);// disable systic timer

}






