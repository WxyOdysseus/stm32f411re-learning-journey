/*
 * uart.h
 *
 *  Created on: 2026年9月22日
 *      Author: 26412
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"


void uart_driver_init(void);
int __io_putchar(int ch);

#endif /* UART_H_ */


