#include "bsp_dma.h"

unsigned char arr[DATA_SIZE];

void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	// 使能AHB总线上挂载的DMA外设时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)arr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = DATA_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	
	// 使能DMA1的通道4(USART1_TX)
	DMA_Cmd(DMA1_Channel4, ENABLE);
}
