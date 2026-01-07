#ifndef __BSP_SPI_MAX6675_H__
#define __BSP_SPI_MAX6675_H__

#include <stm32f10x.h>

#define MAX6675_CS_LOW	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)
#define MAX6675_CS_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)

void SPI1_Configuration(void);

uint16_t SPI_ReadData(void);

#endif	// __BSP_SPI_MAX6675_H__
