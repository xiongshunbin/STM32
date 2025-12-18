#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_adc.h"
#include "bsp_tim2.h"
#include "bsp_rtc.h"

int main(void)
{
	u16 TIMCompare2;
	
	SysTick_Configuration();
	
	TIM2_PWM_Configuration();
	
	while (1)
	{
		for (TIMCompare2 = 0; TIMCompare2 < 20000; ++TIMCompare2)
		{
			TIM_SetCompare2(TIM2, TIMCompare2);
			Delay_us(50);
		}
		
		for (TIMCompare2 = 20000; TIMCompare2 > 0; --TIMCompare2)
		{
			TIM_SetCompare2(TIM2, TIMCompare2);
			Delay_us(50);
		}
	}
}
