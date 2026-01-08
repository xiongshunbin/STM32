#include "bsp_hcsr04.h"

void TIM2_Count_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	// 开启APB1总线上的TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;			// 65536个计数周期
	TIM_TimeBaseStructure.TIM_Prescaler = 0x47;			// 72分频
	// TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;	// 设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 使能TIM2定时器
	TIM_Cmd(TIM2, ENABLE);
	// 暂时先关闭TIM2定时器的时钟, 等全部初始化结束后正式使用定时器时再开启
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}

/*
 *	PB6(output) --> TRIG
 *	PB7(input)  --> ECHO
*/
void HCSR04_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOB外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 将GPIOB的PB6设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 将GPIOB的PB7设置为浮空输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
