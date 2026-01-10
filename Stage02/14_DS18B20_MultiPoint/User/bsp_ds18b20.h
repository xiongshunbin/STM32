#ifndef __BSP_DS18B20_H__
#define __BSP_DS18B20_H__

/**
 * DS18B20_0: 28 D3 60 71 00 00 00 B5
 * DS18B20_1: 28 B8 63 71 00 00 00 C0
 */

#include <stm32f10x.h>
#include <stdio.h>
#include "bsp_SysTick.h"

#define DS18B20_Data_Out(BitVal)		GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(BitVal))

void DS18B20_GPIO_Configuration(void);

void DS18B20_Init(void);

float DS18B20_Get_Temperature(int DS18B20_No);

void DS18B20_ReadROM_ID(void);

#endif	// __BSP_DS18B20_H__
