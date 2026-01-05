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
#include "bsp_digital_tube.h"
#include "bsp_74HC595.h"

unsigned int count = 0;

int main(void)
{
	SysTick_Configuration();
	
	DigitalTube_74HC595_GPIO_Configuration();
	
	TIM2_BaseConfiguration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while (1)
	{
		/*
		DigitalTube_74HC595_SendData(num[4], 0);
		DigitalTube_74HC595_SendData(num[3], 1);
		DigitalTube_74HC595_SendData(num[2], 2);
		DigitalTube_74HC595_SendData(num[1], 3);
		*/
		
		if (count > 9999)
		{
			count = 0;
		}
		
		Display(count);
	}
}
