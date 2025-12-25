#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include <stm32f10x.h>
#include <stdio.h>

#define MAX_RECVDATA_SIZE 255
#define LED_ON 	0x11
#define LED_OFF 0x00

typedef enum
{
	LED_1 = 1,
	LED_2 = 2,
	LED_3 = 3,
	LED_4 = 4
}LED_NUM;

void UART1_Configuration(void);

void UART1_NVIC_Init(void);

void USART_SendString(USART_TypeDef* USARTx, const char* pt);

#endif	// __BSP_UART_H__
