#ifndef __LED_KEY_H__
#define __LED_KEY_H__

#include "stm32f10x.h"

#define KEY_ON 	0
#define KEY_OFF	1

void LED_Configuration(void);
void Key_Configuration(void);
int Key_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void Delay(unsigned long nCount);

#endif	// __LED_KEY_H__
