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
	
	while (1)
	{
		USART_SendData(USART1, 0x41);
		Delay_us(1000000);
	}
}
