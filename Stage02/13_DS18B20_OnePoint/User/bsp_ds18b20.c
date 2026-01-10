#include "bsp_ds18b20.h"

void DS18B20_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 将GPIOB的PB6设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS18B20_Mode_IPU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 将GPIOB的PB6设置为上拉输入模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// PB6 -> DS18B20_DQ
void DS18B20_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIOB外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 将GPIOB的PB6设置为通用推挽输出模式, 工作频率50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS18B20_Init(void)
{
	DS18B20_Mode_Out_PP();	// 通用推挽输出设置产生480us的复位脉冲
	
	DS18B20_Data_Out(0);
	Delay_us(750);
	DS18B20_Data_Out(1);
	Delay_us(15);
	
	DS18B20_Mode_IPU();		// 上拉输入模式捕获DS180B20的存在脉冲
	
	// 等待低电平存在脉冲
	while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) != 0);
	
	// 等待低电平结束, 初始化完毕
	while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) != 1);
}

void DS18B20_WriteByte(uint8_t data)
{
	int i;
	
	DS18B20_Mode_Out_PP();
	
	for (i = 0; i < 8; ++i)
	{
		if ((data & 0x01) == 1)	// 写1时序
		{
			DS18B20_Data_Out(0);
			Delay_us(8);
			
			DS18B20_Data_Out(1);
			Delay_us(58);
		}
		else					// 写0时序
		{
			DS18B20_Data_Out(0);
			Delay_us(70);
			
			DS18B20_Data_Out(1);
			Delay_us(2);
		}
		data >>= 1;
	}
}

uint8_t DS18B20_ReadByte(void)
{
	int i;
	uint8_t data = 0;
	
	for (i = 0; i < 8; ++i)
	{
		DS18B20_Mode_Out_PP();
		DS18B20_Data_Out(0);
		Delay_us(10);
		
		DS18B20_Mode_IPU();
		data |= GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) << i;
		Delay_us(55);
	}
	
	return data;
}

float DS18B20_Get_Temperature(void)
{
	uint8_t LS_Byte, MS_Byte;
	short temp;
	float temperature;
	
	// 开启温度转换
	DS18B20_Init();				// 1.初始化
	DS18B20_WriteByte(0xCC);	// 2.ROM操作指令, 单DS18B20, 忽略ROM指令
	DS18B20_WriteByte(0x44);	// 3.温度转换指令
	
	// 读取温度值
	DS18B20_Init();				// 1.初始化
	DS18B20_WriteByte(0xCC);	// 2.ROM操作指令, 单DS18B20, 忽略ROM指令
	DS18B20_WriteByte(0xBE);	// 3.读暂存器指令
	
	LS_Byte = DS18B20_ReadByte();
	MS_Byte = DS18B20_ReadByte();
	
	temp = MS_Byte << 8;
	temp |= LS_Byte;
	
	if (temp < 0)	// 负温度值
	{
		temperature = -(~temp + 1) * 0.0625;
	}
	else
	{
		temperature = temp * 0.0625;
	}
	
	return temperature;
}
