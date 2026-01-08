#ifndef __BSP_74HC595_H__
#define __BSP_74HC595_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"
#include "bsp_digital_tube.h"

void DigitalTube_74HC595_GPIO_Configuration(void);

void DigitalTube_74HC595_SendData(uint8_t number, uint8_t tubeNo);

void Display(unsigned int number);

#endif	// __BSP_74HC595_H__
