<!-- Markdown全局样式 -->

<!-- 表格居中 -->
<style>
table
{
    margin: auto;
}
</style>

<!-- -------------------------------------- -->

# 自定义UART数据格式

> 自定义UART数据格式常常适用于**CPU与CPU之间**、**外设与CPU之间**的通信。

## 1.目的
在串口调试助手上发送一串数据，控制4个LED灯的亮灭状态。

## 2.内容
    自定义的数据帧格式为：起始位(1B) + 数据长度(1B) + LED灯状态(2B) + 校验位(1B) + 结束位(1B)
其中，LED灯状态(2B)由LED灯序号(1B)和状态(1B)组成，LED有两种状态：`0x00`表示灭，`0x11`表示亮。一条数据帧报文中可同时包含多组LED灯状态。校验位 = 数据长度 + LED灯状态。那么，使LED1点亮的命令格式如下表所示：

|   起始位  | 数据长度 | LED灯序号 |  状态  |   校验位  |   结束位  |
|   :---:  | :---:  |   :---:   | :---: |   :---:  |   :---:  |
|   0xAA   |  0x06  |    0x01   |  0x11 |   0x18   |   0xFF   |

## 3.示例
eg1:LED1和LED3点亮: `AA 08 01 11 03 11 2E FF`

eg2:LED1熄灭，LED2灯点亮: `AA 08 01 00 02 11 1C FF`

eg3: LED2、LED3熄灭，LED4点亮: `AA 0A 02 00 03 00 04 11 24 FF`

## 4.实现
```c
// USART配置
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

// 初始化NVIC
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

// USART中断处理函数的实现
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

int main(void)
{
	LED_Configuration();

	UART1_Configuration();
	
	UART1_NVIC_Init();
	
	while (1)
	{

	}
}
```