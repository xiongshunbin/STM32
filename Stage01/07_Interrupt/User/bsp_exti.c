#include "bsp_exti.h"

void wait(unsigned long nCount)
{
	while (nCount--);
}

void PA0_EXTI0_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	// 使能GPIOA外设时钟和功能复用IO时钟(外部中断)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	// 初始化NVIC(向量中断控制器)管理EXTI0(外部中断)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// 将GPIOA的PA0设置为上拉输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// 将PA0用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	// 初始化EXTI, 以下降沿方式触发中断请求
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

/*
 * 当中断发生时, 中断标志位会自动发生置位;
 * 当中断服务程序处理完中断后, 需要手动清除中断标志位, 否则将持续触发中断。
*/
void EXTI0_IRQHandler(void)
{
	// 检查指定的EXTI0线路是否触发中断请求
	ITStatus EXTIStatus;
	EXTIStatus = EXTI_GetITStatus(EXTI_Line0);
	if (EXTIStatus == SET)
	{
		GPIOA->ODR ^= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
		// wait(0xfffff);
		// 清除EXTI0线路中断标志位
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
