#include "music.h"

/*
  音符: DO RE M FA SO LA SI
  频率单位: Hz
*/
// 低音	DO
unsigned int BassArray[] = { 262, 294, 330, 349, 392, 440, 494 };			// 低音

unsigned int AltoArray[] = { 523, 587, 659, 698, 784, 880, 988 };			// 中音

unsigned int TrebleArray[] = { 1046, 1175, 1318, 1397, 1568, 1760, 1967};	// 高音

unsigned int music_little_star[][2] = 
{
	{Alto_DO, 400000}, {Alto_DO, 400000}, {Alto_SO, 400000}, {Alto_SO, 400000}, {Alto_LA, 400000}, {Alto_LA, 400000}, {Alto_SO, 800000},	// 一闪一闪亮晶晶
	{Alto_FA, 400000}, {Alto_FA, 400000}, {Alto_M, 400000}, {Alto_M, 400000}, {Alto_RE, 400000}, {Alto_RE, 400000}, {Alto_DO, 800000},		// 满天都是小星星
	{Alto_SO, 400000}, {Alto_SO, 400000}, {Alto_FA, 400000}, {Alto_FA, 400000}, {Alto_M, 400000}, {Alto_M, 400000}, {Alto_RE, 800000},		// 挂在天上放光明
	{Alto_SO, 400000}, {Alto_SO, 400000}, {Alto_FA, 400000}, {Alto_FA, 400000}, {Alto_M, 400000}, {Alto_M, 400000}, {Alto_RE, 800000},		// 他是我们的小眼睛
	{Alto_DO, 400000}, {Alto_DO, 400000}, {Alto_SO, 400000}, {Alto_SO, 400000}, {Alto_LA, 400000}, {Alto_LA, 400000}, {Alto_SO, 800000},	// 一闪一闪亮晶晶
	{Alto_FA, 400000}, {Alto_FA, 400000}, {Alto_M, 400000}, {Alto_M, 400000}, {Alto_RE, 400000}, {Alto_RE, 400000}, {Alto_DO, 800000},		// 满天都是小星星
	{0, 0}
};

void Sound(unsigned int frequency)
{
	TIM4->ARR = (unsigned int)(1000000 * 1.0 / frequency + 0.5) - 1;
	TIM4->CCR3 = (unsigned int)(500000 * 1.0 / frequency + 0.5);
}
