#ifndef __BSP_DS18B20_H__
#define __BSP_DS18B20_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"

#define DS18B20_Data_Out(BitVal)		GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(BitVal))

void DS18B20_GPIO_Configuration(void);

void DS18B20_Init(void);

float DS18B20_Get_Temperature(void);

#endif	// __BSP_DS18B20_H__
