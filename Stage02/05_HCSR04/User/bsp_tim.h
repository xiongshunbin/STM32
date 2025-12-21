#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#include <stm32f10x.h>
#include "LED_Key.h"

void TIM2_BaseConfiguration(void);
void TIM2_PWM_Configuration(void);

void TIM4_PWM_Configuration(void);

#endif	// __BSP_TIM2_H__
