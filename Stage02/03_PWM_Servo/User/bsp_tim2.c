#include "bsp_tim2.h"

unsigned int times = 0;

void TIM2_BaseConfiguration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	// 开启APB1总线上的TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 初始化NVIC(向量中断控制器)管理TIM2(TIM2定时器中断)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// 初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = 0x3E7;			// 1000个计数周期
	TIM_TimeBaseStructure.TIM_Prescaler = 0x47;			// 72分频
	// TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;	// 设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 清除TIM2的更新标志位
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	// 使能TIM2的中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// 使能TIM2定时器
	TIM_Cmd(TIM2, ENABLE);
	
	// 暂时先关闭TIM2定时器的时钟, 等全部初始化结束后正式使用定时器时再开启
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		times ++;
		if (times == 500)
		{
			LED_TOGGLE;
			times = 0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM2_PWM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	// 开启APB2总线上的GPIOA外设和APB1总线上的TIM2外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 将GPIOA的PA1设置为复用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = 0x4E1F;			// 20000个计数周期 period --> 20ms
	TIM_TimeBaseStructure.TIM_Prescaler = 0x47;			// 72分频
	// TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;	// 设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}
