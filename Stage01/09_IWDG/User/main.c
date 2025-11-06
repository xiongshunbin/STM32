#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"

int main(void)
{
	SysTick_Configuration();
	
	LED_Configuration();
	Key_Configuration();
	
	IWDG_Configuration();
	
	LED_TOGGLE;
	Delay_us(100000);
	LED_TOGGLE;
	Delay_us(100000);
	
	while (1)
	{
		if (Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON)
		{
			IWDG_FeedDog();
		}
		Delay_us(1000);
	}
}
