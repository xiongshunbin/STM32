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
	SysTick_Configuration();
	
	UART1_Configuration();
	
	ADC_Configuration();
	
	while (1)
	{

	}
}
