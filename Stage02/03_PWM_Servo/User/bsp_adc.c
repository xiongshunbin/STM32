#include "bsp_adc.h"

uint16_t ADC_ConvertVal;

void ADC_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// 使能AHB总线上挂载的DMA外设时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// 使能APB2总线上挂载的ADC1外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	// 初始化DMA
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertVal;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	// 使能DMA1的通道1(ADC1)
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	// 初始化ADC1
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 设置ADC的输入时钟为9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);		// 频率 <= 14MHz
	// 设置ADC1的通道16的采样时间
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);	// Tconv = 55.5 + 12.5 = 68
	// 使能ADC1通道16的温度传感器
	ADC_TempSensorVrefintCmd(ENABLE);
	
	// 使能ADC1的DMA请求
	ADC_DMACmd(ADC1, ENABLE);
	// 使能ADC1	
	ADC_Cmd(ADC1, ENABLE);
	// 重置ADC1的校准寄存器
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) != RESET);
	// 开始ADC1的校准状态
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) != RESET);
	
	// 使能ADC1的软件转换启动功能
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
