#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"
#include "bsp_dma.h"

int main(void)
{
	int i;
	
	SysTick_Configuration();
	
	LED_Configuration();
	
	UART1_Configuration();
	
	DMA_Configuration();
	
	for (i = 0; i < DATA_SIZE; i++)
	{
		arr[i] = 'A';
	}
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	
	while (1)
	{
		LED_TOGGLE;
		Delay_us(200000);
		LED_TOGGLE;
		Delay_us(200000);
	}
}
