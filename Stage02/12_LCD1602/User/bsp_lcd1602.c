#include "bsp_lcd1602.h"

void LCD1602_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	
	// 将GPIOA的PA5、PA9、PA10、PA11、PA12设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 将GPIOB的PB5、PB12、PB13、PB14、PB15设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 将GPIOC的PC13设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// 读取忙信号, 等待LCD1602就绪
void LCD1602_WaitReady(void)
{
	// 将PC13改为浮空输入模式
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00400000;
	
	LCD1602_RS_Low();
	LCD1602_RW_High();
	LCD1602_EN_High();
	Delay_us(5000);
	
	while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) != 0x00);
	
	// 当LCD1602就绪后, 将PC13(DB7)改为通用推挽输出模式
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00300000;
	
	LCD1602_EN_Low();
}

void LCD1602_SetDataBit(DataBit bit, int BitVal)
{
	switch (bit)
	{
		case LCD1602_DB0:	LCD1602_DB0_Set(BitVal);	break;
		case LCD1602_DB1:	LCD1602_DB1_Set(BitVal);	break;
		case LCD1602_DB2:	LCD1602_DB2_Set(BitVal);	break;
		case LCD1602_DB3:	LCD1602_DB3_Set(BitVal);	break;
		case LCD1602_DB4:	LCD1602_DB4_Set(BitVal);	break;
		case LCD1602_DB5:	LCD1602_DB5_Set(BitVal);	break;
		case LCD1602_DB6:	LCD1602_DB6_Set(BitVal);	break;
		case LCD1602_DB7:	LCD1602_DB7_Set(BitVal);	break;
		default:			break;
	}
}

// 写命令
void LCD1602_WriteCmd(uint8_t cmd)
{
	int i;
	
	LCD1602_WaitReady();
	
	LCD1602_RS_Low();
	LCD1602_RW_Low();
	
	for (i = 0; i < 8; ++i)
	{
		LCD1602_SetDataBit((DataBit)(1 << i), (cmd >> i) & 0x01);
	}
	
	LCD1602_EN_High();
	LCD1602_EN_Low();
}

// 写数据
void LCD1602_WriteData(uint8_t data)
{
	int i;
	
	LCD1602_WaitReady();
	
	LCD1602_RS_High();
	LCD1602_RW_Low();
	
	for (i = 0; i < 8; ++i)
	{
		LCD1602_SetDataBit((DataBit)(1 << i), (data >> i) & 0x01);
	}
	
	LCD1602_EN_High();
	LCD1602_EN_Low();
}

void LCD1602_Init(void)
{
	// LCD1602 功能设定指令
	LCD1602_WriteCmd(0x38);		// 数据总线为 8 位, 2 行显示, 5 x 7 点阵
	LCD1602_WriteCmd(0x0C);		// 显示功能关, 关闭光标
	LCD1602_WriteCmd(0x06);		// 写入新数据后显示屏不移动, 写入新数据后光标右移
	LCD1602_WriteCmd(0x01);		// 清屏
}

void LCD1602_ClearScreen(void)
{
	LCD1602_WriteCmd(0x01);
}

void LCD1602_SetCursor(uint8_t x, uint8_t y)
{
	uint8_t addr;
	
	if (y == 0)
	{
		addr = 0x00 + x;
	}
	else if (y == 1)
	{
		addr = 0x40 + x;
	}
	
	LCD1602_WriteCmd((0x80 | addr));
}

void LCD1602_ShowChar(uint8_t x, uint8_t y, uint8_t data)
{
	LCD1602_SetCursor(x, y);
	LCD1602_WriteData(data);
}

void LCD1602_ShowString(uint8_t x, uint8_t y, unsigned char* str)
{
	LCD1602_SetCursor(x, y);
	while (*str != '\0')
	{
		LCD1602_WriteData(*str++);
	}
}
