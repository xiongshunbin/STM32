#include "LED_Key.h"
#include "bsp_exti.h"

int main(void)
{
	LED_Configuration();
	PA0_EXTI0_Configuration();
	
	while (1)
	{
		
	}
}
