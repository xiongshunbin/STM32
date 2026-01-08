#ifndef __BSP_LCD1602_H__
#define __BSP_LCD1602_H__

#include <stm32f10x.h>

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

#endif	// __BSP_LCD1602_H__
