#include "bsp_rtc.h"

unsigned int days_in_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void RTC_Configuration(void)
{
	// 1.使能电源和后备接口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
	// 2.使能对后备寄存器和RTC的访问
	PWR_BackupAccessCmd(ENABLE);
	// 3.复位RTC_PRL、RTC_ALR、RTC_CNT和RTC_DIV寄存器
	BKP_DeInit();
	// 4.使能LSE
	RCC_LSEConfig(RCC_LSE_ON);
	// 5.等待直到LSE就绪为止
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	// 6.选择LSE(频率: 32.768KHz)作为RTC时钟
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	// 7.使能RTC时钟, RTC开始工作
	RCC_RTCCLKCmd(ENABLE);
	// 8.等待之前RTC寄存器的写操作完成
	RTC_WaitForLastTask();
	// 9.等待寄存器同步标志位置1
	RTC_WaitForSynchro();
	// 10.设置分频系数为32768
	RTC_SetPrescaler(0x7FFF);		// 32767 = 2 ^ 15 - 1
	// 11.等待之前RTC寄存器的写操作完成
	RTC_WaitForLastTask();
}

void Time_Display(uint32_t TimeVal)
{
	struct rtc_tm tm;
	unsigned int days, hms;
	unsigned int i;
	
	days = TimeVal / (24 * 60 * 60);
	hms = TimeVal % (24 * 60 * 60);
	
	tm.hour = hms / (60 * 60);
	tm.minute = hms % (60 * 60) / 60;
	tm.second = hms % (60 * 60) % 60;
	
	for (i = 1970; days >= days_in_year(i); ++i)
	{
		days -= days_in_year(i);
	}
	
	tm.year = i;
	if (Leap_Year(i))
	{
		days_in_month[2] = 29;
	}
	else
	{
		days_in_month[2] = 28;
	}
	for (i = 1; days >= days_in_month[i]; ++i)
	{
		days -= days_in_month[i];
	}
	tm.month = i;
	tm.day = days + 1;
	
	printf("%d-%d-%d %d:%d:%d\n", tm.year, tm.month, tm.day, tm.hour, tm.minute, tm.second);
}
