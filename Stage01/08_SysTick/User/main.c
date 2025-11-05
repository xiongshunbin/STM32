#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"

int main(void)
{
	SysTick_Configuration();
	
	LED_Configuration();
	
	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, Bit_SET);
		Delay_us(100000);		// 1s = 1000000us
		GPIO_WriteBit(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, Bit_RESET);
		Delay_us(100000);		// 1s = 1000000us
	}
}
