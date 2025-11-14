#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"

int main(void)
{
	SysTick_Configuration();
	
	UART1_Configuration();
	
	UART1_NVIC_Init();
	
	while (1)
	{
		
	}
}
