#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include <stm32f10x.h>

#define ADC_DR 		0x4001244C

extern uint16_t ADC_ConvertVal;

void ADC_Configuration(void);

#endif	// __BSP_ADC_H__
