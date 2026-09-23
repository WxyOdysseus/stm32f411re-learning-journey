/*propose: 重定向printf*/
/*现在，先完成uart_tx driver*/
/*在uart2上有Tx线，通过这个发送消息*/
/*uart2 与APB1相连*/
/*在af mapping 发现：uart_Tx 输出到PA2 在GPIO眼中是AF07*/
/*GPIOA 和AHB1相连*/



#include<stdio.h>
#include "uart_receive_dr.h"
#include<stdint.h>
#include "stm32f4xx.h"


#define AHB1ENR_EN_OP		(1U<<0)//AHB1ENR enable operator
#define AHB1ENR_C_EN_OP		(1U<<2)
#define GPIOA_MODER_L_CLER	(1U<<10)//GPIOA_MODER low bit cleaner
#define GPIOA_MODER_H_CLER	(1U<<11)//GPIOA_MODER high bit cleaner
#define GPIOA_MODER_SET_OP	(1U<<10)//GPIOA_MODER set operator

#define GPIOC_MODER_L_CLER	(1U<<26)
#define GPIOC_MODER_H_CLER	(1U<<27)
#define GPIOC_MODER_SET_OP	(0x00000000)//00means input mode
void LED_init(void);


int main(void)
{


	usart_rx_init();
	LED_init();
	for(volatile int32_t i=0;i<100;i++){}
	while(1)
	{
		if('1'==read_func())
		{
			GPIOA->BSRR |=(1U<<5);//set
		}
		else
		{
			GPIOA->BSRR |=(1U<<21);//reset
		}

	}


}




void LED_init(void)
{
	/***initialize the LED***/
	/*enable RCC->AHB1ENR to enable clock access of AHB1*/
	if(!(RCC->AHB1ENR & AHB1ENR_EN_OP))//check whether the R has been set
	{
		RCC->AHB1ENR |= AHB1ENR_EN_OP;
	}
	/*configure GPIOA MODER*/
	/*clean up GPIOA_MODER*/
	GPIOA->MODER &= ~GPIOA_MODER_L_CLER;
	GPIOA->MODER &= ~GPIOA_MODER_H_CLER;
	/*set*/
	GPIOA->MODER |= GPIOA_MODER_SET_OP;
	/*configure GPIOA BSRR to high,so that the LED can light up,\
	 but can't appear in the init*/
}
