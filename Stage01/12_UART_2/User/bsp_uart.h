#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include <stm32f10x.h>
#include <stdio.h>

void UART1_Configuration(void);

void USART_SendString(USART_TypeDef* USARTx, const char* pt);

#endif	// __BSP_UART_H__
