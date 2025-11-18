#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"

int main(void)
{
	SysTick_Configuration();
	
	LED_Configuration();
	
	PA5_EXTI5_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	while (1)
	{
		LED_TOGGLE;
		Delay_us(200000);
		LED_TOGGLE;
		Delay_us(200000);
	}
}
