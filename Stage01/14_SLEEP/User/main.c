#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"

int main(void)
{
	int i;
	
	SysTick_Configuration();
	
	LED_Configuration();
	
	PA0_EXTI0_Configuration();
	
	while (1)
	{
		for (i = 0; i < 10; i++)
		{
			LED_TOGGLE;
			Delay_us(200000);
			LED_TOGGLE;
			Delay_us(200000);
		}
		
		__WFI();
	}
}
