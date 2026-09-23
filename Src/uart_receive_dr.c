/*uart_rx   usart2*/
/*usart2 在 apb1 上*/
/*查阅usart2的reference manual*/

/*pa3   af07*/


/*USART_CR1 M  either 8 or 9*/
/*start bit is detected 1 1 1 0 X 0 X 0 X 0 0 0 0*/
/*If the sequence is not complete, the start bit detection aborts and the receiver returns to the
idle state (no flag is set) where it waits for a falling edge.*/

/*1.
Enable the USART by writing the UE bit in USART_CR1 register to 1.
2.
Program the M bit in USART_CR1 to define the word length.
3.
Program the number of stop bits in USART_CR2.
4.
Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take
place. Configure the DMA register as explained in multibuffer communication. STEP 3
5.
Select the desired baud rate using the baud rate register USART_BRR
6.
Set the RE bit USART_CR1. This enables the receiver which begins searching for a
start bit.*/


/*•
The RXNE bit is set. It indicates that the content of the shift register is transferred to the
RDR. In other words, data has been received and can be read (as well as its
associated error flags).
•
An interrupt is generated if the RXNEIE bit is set.
•
The error flags can be set if a frame error, noise or an overrun error has been detected
during reception.
•
In multibuffer, RXNE is set after every byte received and is cleared by the DMA read to
the Data Register.
•
In single buffer mode, clearing the RXNE bit is performed by a software read to the
USART_DR register. The RXNE flag can also be cleared by writing a zero to it. The
RXNE bit must be cleared before the end of the reception of the next character to avoid
an overrun error.*/



#include "stm32f4xx.h"
#include "uart_receive_dr.h"



static int16_t comput_uart_div(int32_t PeriperalCLK,int32_t Baudrate)
{
	return (int16_t)((PeriperalCLK+(Baudrate/2U))/Baudrate);
}

static void uart_set_baudrate(USART_TypeDef *USARTx,int32_t PeriperalCLK,int32_t Baudrate)//这个函数抄了一下课程的
{
	USARTx->BRR = comput_uart_div(PeriperalCLK,Baudrate);
}

void usart_rx_init(void)
{
	/*********enable GPIO hardware********/
	/***enable clock of GPIOA*****/
	RCC->AHB1ENR |=(1U<<0);

	/**********set GPIO parameter*********/

	/***set GPIOA to AF mode***/
	GPIOA->MODER &=~((1U<<6)|(1U<<7));
	GPIOA->MODER |=((1U<<7));
	/***set pin to of connection***/
	GPIOA->AFR[0] &=~(1U<<15);
	GPIOA->AFR[0] |=((1U<<12)|(1U<<13)|(1U<<14));

	/************enable  usart2 hardware*******/
	/***enable clock of usart2***/
	RCC->APB1ENR |=(1U<<17);

	/***Enable the USART by writing the UE bit in USART_CR1 register to 1.*/
	USART2->CR1 |=(1U<<13);
	/***Select the desired baud rate using the baud rate register USART_BRR**/
	uart_set_baudrate(USART2,16000000,115200);
	/***Set the RE bit USART_CR1. This enables the receiver which begins searching for a
start bit.*/
	USART2->CR1 |=(1U<<2);

}

uint8_t read_func(void)
{
	while(!(USART2->SR&(1U<<5))){};
	return (uint8_t)(USART2->DR);
}







