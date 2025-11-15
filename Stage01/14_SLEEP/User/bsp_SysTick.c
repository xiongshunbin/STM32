#include "bsp_SysTick.h"

unsigned int TimingDelay;

void SysTick_Configuration(void)
{
	// 初始化定时器
	while (SysTick_Config(72) == 1);
	
	// 暂时关闭定时器, 等待使用前开启
	SysTick->CTRL &= ~(1 << 0);
}

void Delay_us(unsigned int n)
{
	TimingDelay = n;
	// 开启SysTick定时器
	SysTick->CTRL |= (1 << 0);
	
	while (TimingDelay != 0);
	// 暂时关闭定时器
	SysTick->CTRL &= ~(1 << 0);
}
