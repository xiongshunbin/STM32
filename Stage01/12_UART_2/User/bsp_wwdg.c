#include "bsp_wwdg.h"

unsigned char WWDG_CNT = 0x7F;

void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void WWDG_Configuration(unsigned char tr, unsigned char wr, unsigned int pr)
{
	// 使能WWDG外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// 设置WWDG计数器值
	WWDG_CNT = tr & WWDG_CNT;
	// 设置WWDG上限窗口值
	WWDG_SetWindowValue(wr);
	// 设置WWDG预分频值
	WWDG_SetPrescaler(pr);
	// 使能WWDG并装入计数器值
	WWDG_Enable(WWDG_CNT);
	
	// 初始化NVIC(向量中断控制器)管理WWDG(窗口看门狗)
	WWDG_NVIC_Init();
	// 清除早期唤醒中断标志位
	WWDG_ClearFlag();
	// 使能WWDG早期唤醒中断(EWI)
	WWDG_EnableIT();
}

void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(WWDG_CNT);	// "喂狗"
	WWDG_ClearFlag();			// 清除中断标志位
}
