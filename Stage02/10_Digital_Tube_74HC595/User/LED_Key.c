#include "LED_Key.h"
#include "bsp_Systick.h"

enum Scan_Mode mode;

void Delay(unsigned long nCount)
{
	while (nCount--);
}

/*
 PA1 -> LED1
 PA2 -> LED2
 PA3 -> LED3
 PA4 -> LED4
*/
void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOA外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 将GPIOA的PA1~PA4设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// PA0 -> KEY1
void Key_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOA外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 将GPIOA的PA0设置为上拉输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int Key_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
{
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0)
	{
		Delay(1000);
		if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0)
		{
			while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0);
			return KEY_ON;
		}
	}
	return KEY_OFF;
}

/*
 PA0 -> R1
 PA1 -> R2
 PA2 -> R3
 PA3 -> R4
 PA4 -> C1
 PA5 -> C2
 PA6 -> C3
 PA7 -> C4
*/

// 行扫描 -> 行号
uint8_t Matrix_Row_Scan(void)
{
	uint8_t key = 0;
	uint8_t row = 0;		// 行号
	GPIO_InitTypeDef GPIO_InitStructure;
	mode = COLUMN_ROW;
	
	// 将GPIOA的PA0~PA3设置为上拉输入模式, 工作频率为50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 将GPIOA的PA4~PA5设置为通用推挽输出模式且输出低电平, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
	
	if ((GPIOA->IDR & 0x0F) != 0x0F)
	{
		Delay_us(1000);				// 消抖
		key = GPIOA->IDR & 0x0F;
		if (key != 0x0F)
		{
			switch (key)
			{
				case 0x0E:	row = 1;	break;
				case 0x0D:	row = 2;	break;
				case 0x0B:	row = 3;	break;
				case 0x07:	row = 4;	break;
				default:	break;
			}
		}
	}
	return row;
}

// 列扫描 -> 列号
uint8_t Matrix_Column_Scan(void)
{
	uint8_t key = 0;
	uint8_t column = 0;		// 列号
	GPIO_InitTypeDef GPIO_InitStructure;
	mode = ROW_COLUMN;
	
	// 将GPIOA的PA0~PA3设置为通用推挽输出模式且输出低电平, 工作频率为50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, Bit_RESET);
	
	// 将GPIOA的PA4~PA5设置为上拉输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	if ((GPIOA->IDR & 0xF0) != 0xF0)
	{
		Delay_us(1000);				// 消抖
		key = GPIOA->IDR & 0xF0;
		if (key != 0xF0)
		{
			switch (key)
			{
				case 0xE0:	column = 1;	break;
				case 0xD0:	column = 2;	break;
				case 0xB0:	column = 3;	break;
				case 0x70:	column = 4;	break;
				default:	break;
			}
		}
	}
	return column;
}

// 行列线扫描法
int Matrix_Key_Scan(void)
{
	int row = Matrix_Row_Scan();
	int column = Matrix_Column_Scan();
	if (row == 0 || column == 0)
	{
		return 0;
	}

	switch (mode)
	{
		case ROW_COLUMN:
			while ((GPIOA->IDR & 0xF0) != 0xF0);
			break;
		case COLUMN_ROW:
			while ((GPIOA->IDR & 0x0F) != 0x0F);
			break;
		default:
			break;
	}
	
	return (row - 1) * COLUMN_SIZE + column;
}
