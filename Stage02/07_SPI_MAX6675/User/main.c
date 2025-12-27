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
	uint16_t data;
	unsigned int flag_D2;
	uint16_t temp;
	float temperature;
	
	SysTick_Configuration();
	
	UART1_Configuration();
	
	SPI1_Configuration();
	
	while (1)
	{
		MAX6675_CS_LOW;
		data = SPI_ReadData();
		MAX6675_CS_HIGH;
		
		flag_D2 = data & 0x0004;
		if (flag_D2 == 0)
		{
			temp = (data << 1) >> 3;
			temperature = temp * 0.25;
			printf("Temperature = %4.2f\n", temperature);
		}
		else
		{
			printf("Sensor is broken!\n");
		}
		
		Delay_us(1000000);
	}
}
