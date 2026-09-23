/*
 * uart.c
 *
 *  Created on: 2026年9月22日
 *      Author: 26412
 */


#include "uart.h"

#define AHB1_GPIOA_EN		(1U<<0)
#define APB1_USART2_EN		(1U<<17)
#define GPIOA2_MODER_TO_AF	(2U<<4)

#define AF_conf				(7U<<8)
#define USART_TX_EN			(1U<<3)
#define USART_UE_EN			(1U<<13)

static int16_t comput_uart_div(int32_t PeriperalCLK,int32_t Baudrate);
static void uart_set_baudrate(USART_TypeDef *USARTx,int32_t PeriperalCLK,int32_t Baudrate);
void uart_driver_init(void);
void write_mine(int8_t CH);



int __io_putchar(int ch)
{
	write_mine(ch);

		return ch;
}


void write_mine(int8_t CH)
{
	while(!(USART2->SR &(1U<<7))){}

		USART2->DR= CH;

}


void uart_driver_init(void)//只是封装一连串的动作而已
{
	/*给GPIOA uart2 通电*/
	RCC->AHB1ENR |= AHB1_GPIOA_EN;
	RCC->APB1ENR |= APB1_USART2_EN;
	/*把GPIOA 的PA2变成AF*/
	GPIOA->MODER &=(~(3U<<4));
	GPIOA->MODER |=GPIOA2_MODER_TO_AF;
	/* 设置GPIOA 的pin2 的 AF07为AF  mode */
	GPIOA->AFR[0] &=(~AF_conf);//clear
	GPIOA->AFR[0] |=AF_conf;//configure

	/*设置uart 的发送方向*/
	USART2->CR1 |= USART_TX_EN;//发送方向
	/*设置baud rate*/
	uart_set_baudrate(USART2,16000000,115200);
	/*enabe USART*/
	USART2->CR1 |=USART_UE_EN;

}

static void uart_set_baudrate(USART_TypeDef *USARTx,int32_t PeriperalCLK,int32_t Baudrate)//这个函数抄了一下课程的
{
	USARTx->BRR = comput_uart_div(PeriperalCLK,Baudrate);
}



static int16_t comput_uart_div(int32_t PeriperalCLK,int32_t Baudrate)
{
	return (int16_t)((PeriperalCLK+(Baudrate/2U))/Baudrate);
}
