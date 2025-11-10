#include "LED_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"

int main(void)
{
	SysTick_Configuration();
	
	LED_Configuration();
	
	LED_TOGGLE;
	Delay_us(100000);
	LED_TOGGLE;
	Delay_us(100000);
	
	WWDG_Configuration(0x7F, 0x5F, WWDG_Prescaler_8);
	
	while (1)
	{
		
	}
}
