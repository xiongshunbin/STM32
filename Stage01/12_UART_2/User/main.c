#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"

int main(void)
{
	int i = 0;
	
	SysTick_Configuration();
	
	UART1_Configuration();
	
	while (1)
	{
		printf("Hello World!\n");
		printf("i = %d\n", i++);
		Delay_us(1000000);
	}
}
