#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_adc.h"

int main(void)
{
	float temperature;
	float adcx;
	
	SysTick_Configuration();
	
	UART1_Configuration();
	
	ADC_Configuration();
	
	while (1)
	{
		// Temperature = {(V25 - Vsense) / Avg_Slope} + 25
		adcx = ADC_ConvertVal * 3.3 / 4096;
		temperature = (1.43 - adcx) / 0.0043 + 25;
		printf("Temperature = %.1f\n", temperature);
		Delay_us(1000000);
	}
}
