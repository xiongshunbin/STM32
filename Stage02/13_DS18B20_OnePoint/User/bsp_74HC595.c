#include "bsp_74HC595.h"

/**
 * SCLK -> PB13
 * RCLK -> PB12
 * DIO  -> PB15
*/
void DigitalTube_74HC595_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOB外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 将GPIOB的PB12、PB13、PB15设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);
}

// 串入
void DigitalTube_74HC595_SendByte(uint8_t byte)
{
	int i;
	
	for (i = 0; i < 8; ++i)
	{
		if (byte & 0x80)
		{
			GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
		}
		else
		{
			GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);
		}
		
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);	// 电平拉低
		Delay_us(10);
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);		// RCLK上升沿, 74HC595数据并出
		Delay_us(10);
		
		byte <<= 1;
	}
}

// 并出
void DigitalTube_74HC595_SendData(uint8_t number, uint8_t tubeNo)
{
	DigitalTube_74HC595_SendByte(number);		// 内容
	DigitalTube_74HC595_SendByte(1 << tubeNo);	// 片选 eg: 3(0000 1000)
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);	// 电平拉低
	Delay_us(10);
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);		// RCLK上升沿, 74HC595数据并出
	Delay_us(10);
}

void Display(unsigned int number)
{
	static unsigned int thousand_bit, hundred_bit, ten_bit, single_bit;
	
	thousand_bit = number / 1000;
	hundred_bit = (number % 1000) / 100;
	ten_bit = (number % 1000 % 100) / 10;
	single_bit = number % 10;
	if (number > 999)
	{
		DigitalTube_74HC595_SendData(num[thousand_bit], 3);
	}
	
	if (number > 99)
	{
		DigitalTube_74HC595_SendData(num[hundred_bit], 2);
	}
	
	if (number > 9)
	{
		DigitalTube_74HC595_SendData(num[ten_bit], 1);
	}
	
	DigitalTube_74HC595_SendData(num[single_bit], 0);
}
