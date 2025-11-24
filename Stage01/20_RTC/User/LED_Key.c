#include "LED_Key.h"

void Delay(unsigned long nCount)
{
	while (nCount--);
}

/*
 PA1 -> LED1
 PA2 -> LED2
 PA3 -> LED3
 PA4 -> LED4
*/
void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOA外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 将GPIOA的PA1~PA4设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// PA0 -> KEY1
void Key_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOA外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 将GPIOA的PA0设置为上拉输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int Key_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0)
	{
		Delay(1000);
		if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0)
		{
			while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0);
			return KEY_ON;
		}
	}
	return KEY_OFF;
}
