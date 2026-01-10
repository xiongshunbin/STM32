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
#include "bsp_lcd1602.h"
#include "bsp_ds18b20.h"

unsigned int count = 0;

int main(void)
{
	SysTick_Configuration();
	UART1_Configuration();
	
	DS18B20_GPIO_Configuration();
	DS18B20_Init();
	
	while (1)
	{
		printf("Temperature = %f\n", DS18B20_Get_Temperature());
		
		Delay_us(1000000);
	}
}
