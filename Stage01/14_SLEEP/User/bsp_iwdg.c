#include "bsp_iwdg.h"

// 使能IWDG, 在40KHz LSI下, 每隔1s产生IWDG复位
void IWDG_Configuration(void)
{
	// 使能对寄存器IWDG_PR和IWDG_RLR的写操作
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	// 设置IWDG预分频值
	IWDG_SetPrescaler(IWDG_Prescaler_64);
	// 设置IWDG重装载值
	IWDG_SetReload(625);
	// 按照IWDG重装载寄存器的值重装载IWDG递减计数器
	IWDG_ReloadCounter();
	// 使能IWDG
	IWDG_Enable();
}

void IWDG_FeedDog(void)
{
	IWDG_ReloadCounter();
}
