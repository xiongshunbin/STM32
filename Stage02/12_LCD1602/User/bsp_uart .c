#include "bsp_uart.h"

uint8_t receiveData[MAX_RECVDATA_SIZE] = { 0 };
uint8_t dataSize = 0;

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
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// 使能USART1外设
	USART_Cmd(USART1, ENABLE);
}

void UART1_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// 初始化NVIC(向量中断控制器)管理USART1(串口中断)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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

int fgetc(FILE *stream)
{
	// 等待直到接收缓冲区内非空
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != SET);
	return USART_ReceiveData(USART1);
}

/*
void USART1_IRQHandler(void)
{
	unsigned char ch;
	// 等待直到接收缓冲区内非空
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		ch = USART_ReceiveData(USART1);
		printf("%c\n", ch + 1);
	}
}
*/

// 计算校验和
uint8_t Calc_CheckSum(uint8_t* data, int size)
{
	uint8_t i;
	uint8_t checkSum = 0;
	for (i = 0; i < size; ++i)
	{
		checkSum += *(data + i);
	}
	return checkSum;
}

// 操作LED灯
void LED_Operate(LED_NUM num, uint8_t state)
{
	uint16_t GPIO_Pin;
	BitAction BitVal;
	
	if (state == LED_ON)
		BitVal = Bit_SET;
	else if (state == LED_OFF)
		BitVal = Bit_RESET;
	
	switch (num)
	{
		case LED_1:	GPIO_Pin = GPIO_Pin_1;	break;
		case LED_2:	GPIO_Pin = GPIO_Pin_2;	break;
		case LED_3:	GPIO_Pin = GPIO_Pin_3;	break;
		case LED_4:	GPIO_Pin = GPIO_Pin_4;	break;
		default:	break;
	}
	
	GPIO_WriteBit(GPIOA, GPIO_Pin, BitVal);
}

// 命令处理
void CMD_Process(uint8_t* CMD_Data, int size)
{
	int i;
	
	for (i = 0; i < size; i += 2)
	{
		LED_Operate((LED_NUM)*(CMD_Data + i), *(CMD_Data + i + 1));
	}
}

void USART1_IRQHandler(void)
{
	static uint8_t flag = 0;	// 命令开始标志位 0:未开始 1:命令开始
	static uint8_t index = 1;
	
	unsigned char ch;
	// 等待直到接收缓冲区内非空
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		ch = USART_ReceiveData(USART1);
		if (ch == 0xAA)
		{
			receiveData[0] = 0xAA;
			flag = 1;
		}
		
		if (ch != 0xAA && flag == 1)
		{
			receiveData[index] = ch;
			if (index == 1)
			{
				dataSize = ch;
			}
			index++;
			if (index == dataSize)		// 数据帧结束
			{
				if(Calc_CheckSum(receiveData + 1, dataSize - 3) == receiveData[dataSize - 2] 
					&& receiveData[dataSize - 1] == 0xFF)
				{
					CMD_Process(receiveData + 2, dataSize - 4);
				}
				memset(receiveData, 0, sizeof(receiveData));
				dataSize = 0;
				flag = 0;
				index = 1;
			}
		}
	}
}

void substr(char* dest, const char* src, int start, int len) {
    int i, end;
    end = start + len;
    if (end > strlen(src)) 
	{
        end = strlen(src);
    }
    for (i = start; i < end; i++) 
	{
        *dest++ = src[i];
    }
    *dest = '\0'; // 添加字符串结束标记
}

int UART1_Scanf(unsigned int *pt, unsigned int bits)
{
	unsigned int i = 0;
	uint8_t temp[32] = { 0 };
	*pt = 0;
	
	while (i < bits)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != SET);
		temp[i++] = USART_ReceiveData(USART1);
	}
	
	for (i = 0; i < bits; ++i)
	{
		if (!isdigit(temp[i]))
		{
			*pt = 0;
			return -1;
		}
		*pt = (*pt) * 10 + (temp[i] - '0');
	}
	
	return 0;
}
