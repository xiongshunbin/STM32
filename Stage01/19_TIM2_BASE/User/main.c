#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_adc.h"
#include "bsp_tim2.h"

int main(void)
{
	SysTick_Configuration();
	
	LED_Configuration();
	
	TIM2_BaseConfiguration();
	
	// 开启TIM2定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while (1)
	{
		
	}
}
