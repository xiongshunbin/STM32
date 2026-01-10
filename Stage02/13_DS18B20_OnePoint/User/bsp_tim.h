#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#include <stm32f10x.h>
#include "LED_Key.h"

#define MAX_IC_PEROID 65536	// 当前单次测量的最大周期是65.536ms

extern uint16_t high_value;
extern int complete_flag;
extern unsigned int peroid_times;

void TIM2_BaseConfiguration(void);
void TIM2_PWM_Configuration(void);
void TIM3_IC_Configuration(void);

void TIM4_PWM_Configuration(void);


#endif	// __BSP_TIM2_H__
