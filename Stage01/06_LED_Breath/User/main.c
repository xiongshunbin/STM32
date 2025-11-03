#include "LED_Key.h"

#define deltaT 4000

int main(void)
{
	int i;
	
	LED_Configuration();
	
	while (1)
	{
		for (i = 0; i < deltaT; i++)	// LED逐渐变亮
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
			Delay(deltaT - i);
			GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
			Delay(i);
		}
		
		for (i = 0; i < deltaT; i++)	// LED逐渐变暗
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
			Delay(i);
			GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
			Delay(deltaT - i);
		}
	}
}
