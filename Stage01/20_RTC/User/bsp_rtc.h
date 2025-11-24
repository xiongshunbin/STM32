#ifndef __BSP_RTC_H__
#define __BSP_RTC_H__

#include <stm32f10x.h>
#include <stdio.h>

#define Leap_Year(year)			(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
#define days_in_year(year)		(Leap_Year(year) ? 366 : 365)

struct rtc_tm
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
};

int RTC_Configuration(void);

void Time_Display(uint32_t TimeVal);

void Set_Time(void);

#endif
