#ifndef __BSP_HCSR04_H__
#define __BSP_HCSR04_H__

#include <stm32f10x.h>

// 声速: 340m/s
#define SOUND_VELOCITY	340

#define TRIG_H	GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET)
#define TRIG_L	GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET)
#define ECHO	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)

void TIM2_Count_Configuration(void);
void HCSR04_GPIO_Configuration(void);

#endif	// __BSP_HCSR04_H__
