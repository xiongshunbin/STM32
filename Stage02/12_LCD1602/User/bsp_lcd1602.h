#ifndef __BSP_LCD1602_H__
#define __BSP_LCD1602_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"

#define 	LCD1602_RS_Low()			GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define 	LCD1602_RS_High()			GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define 	LCD1602_RW_Low()			GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define 	LCD1602_RW_High()			GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define 	LCD1602_EN_Low()			GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define 	LCD1602_EN_High()			GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define		LCD1602_DB0_Set(BitVal)		GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(BitVal))
#define		LCD1602_DB1_Set(BitVal)		GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)(BitVal))
#define		LCD1602_DB2_Set(BitVal)		GPIO_WriteBit(GPIOA, GPIO_Pin_9, (BitAction)(BitVal))
#define		LCD1602_DB3_Set(BitVal)		GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction)(BitVal))
#define		LCD1602_DB4_Set(BitVal)		GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)(BitVal))
#define		LCD1602_DB5_Set(BitVal)		GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)(BitVal))
#define		LCD1602_DB6_Set(BitVal)		GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)(BitVal))
#define		LCD1602_DB7_Set(BitVal)		GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(BitVal))

typedef enum
{
	DataBusBit_4 = 0,	// 数据总线为 4 位
	DataBusBit_8 = 1	// 数据总线为 8 位
} DataBusBit;

typedef enum
{
	Show_1_Row= 0,	// 显示 1 行
	Show_2_Row = 1	// 显示 2 行
} ShowxRow;

typedef enum
{
	LCD1602_DB0 = 1 << 0,
	LCD1602_DB1 = 1 << 1,
	LCD1602_DB2 = 1 << 2,
	LCD1602_DB3 = 1 << 3,
	LCD1602_DB4 = 1 << 4,
	LCD1602_DB5 = 1 << 5,
	LCD1602_DB6 = 1 << 6,
	LCD1602_DB7 = 1 << 7
}DataBit;

/*
 * 		LCD1602管脚定义
 * 1.LCD602_VSS		-> 	GND
 * 2.LCD1602_VCC	-> 	5V
 * 3.LCD1602_VEE	-> 	通过电位器接地
 * 4.LCD1602_RS		-> 	PA5
 * 5.LCD1602_R/W	->	PB12
 * 6.LCD1602_E		->	PB13
 * 7.LCD1602_DB0	-> 	PB14
 * 8.LCD1602_DB1	-> 	PB15
 * 9.LCD1602_DB2	-> 	PA9
 * 10.LCD1602_DB3	-> 	PA10
 * 11.LCD1602_DB4	-> 	PA11
 * 12.LCD1602_DB5	->	PA12
 * 13.LCD1602_DB6	-> 	PB5
 * 14>LCD1602_DB7 	-> 	PC13
 * 15.LCD1602_A		->	5V
 * 16.LCD1602_K		->	GND
*/

void LCD1602_GPIO_Configuration(void);

void LCD1602_Init(void);

void LCD1602_ClearScreen(void);		// 清屏指令

// 显示字符
void LCD1602_ShowChar(uint8_t x, uint8_t y, uint8_t data);

// 显示字符串
void LCD1602_ShowString(uint8_t x, uint8_t y, unsigned char* str);

#endif	// __BSP_LCD1602_H__
