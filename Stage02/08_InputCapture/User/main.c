#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_adc.h"
#include "bsp_tim.h"
#include "bsp_rtc.h"
#include "music.h"
#include "bsp_hcsr04.h"
#include "bsp_spi_max6675.h"

int main(void)
{
	SysTick_Configuration();
	
	TIM2_PWM_Configuration();	// 脉冲周期: 20ms
	TIM3_IC_Configuration();	// PA1 -> PA6
	
	UART1_Configuration();
	
	TIM_SetCompare2(TIM2, 15000);	// 占空比: 75%, 即高电平时间为150ms
	
	while (1)
	{
		if (complete_flag == 1)
		{
			printf("High level time: %dus\n", peroid_times * MAX_IC_PEROID + high_value);
			peroid_times = 0;
			complete_flag = 0;
		}
		
		Delay_us(100000);
	}
}
