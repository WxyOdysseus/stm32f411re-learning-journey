/*propose: 重定向printf*/
/*现在，先完成uart_tx driver*/
/*在uart2上有Tx线，通过这个发送消息*/
/*uart2 与APB1相连*/
/*在af mapping 发现：uart_Tx 输出到PA2 在GPIO眼中是AF07*/
/*GPIOA 和AHB1相连*/



#include<stdio.h>
#include "uart.h"
#include<stdint.h>
#include "stm32f4xx.h"


int main(void)
{
	uart_driver_init();
	for(volatile int32_t i=0;i<100;i++){}
	while(1)
	{
		printf("HELLO FROM STM32\r\n");
		printf("MODULIZED\r\n");

	}


}

