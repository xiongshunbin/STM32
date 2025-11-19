#ifndef __BSP_DMA_H__
#define __BSP_DMA_H__

#include <stm32f10x.h>

#define DATA_SIZE 1024
#define USART1_DR 0x40013804

extern unsigned char arr[DATA_SIZE];

void DMA_Configuration(void);

#endif	// __BSP_DMA_H__
