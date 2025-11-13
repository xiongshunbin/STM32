#include "bsp_uart.h"

void UART1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	// 使能GPIOA外设时钟和功能复用IO时钟(USART1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	// 配置PA9 - USART1_TX为复用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置PA10 - USART1_RX为浮空输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化USART1外设
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	
	// 使能USART1外设
	USART_Cmd(USART1, ENABLE);
}

void USART_SendString(USART_TypeDef* USARTx, const char* pt)
{
	while (*pt != '\0')
	{
		// 确保发送缓冲区为空, 只有发送缓冲区为空才继续发送
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) != SET);
		USART_SendData(USARTx, *pt);
		// 等待发送完成
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET);
		pt++;
	}
}

int fputc(int c, FILE* stream)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	USART_SendData(USART1, c);
	// 等待发送完成
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	
	return 0;
}
