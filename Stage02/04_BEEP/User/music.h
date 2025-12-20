#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <stm32f10x.h>

#define TONE_NUM 7

enum Bass
{
	Bass_DO = 262,
	Bass_RE = 294,
	Base_M = 330,
	Bass_FA = 349,
	Base_SO = 392,
	Bass_LA = 440,
	Bass_SI = 494
};

enum Alto
{
	Alto_DO = 523,
	Alto_RE = 587,
	Alto_M = 659,
	Alto_FA = 698,
	Alto_SO = 784,
	Alto_LA = 880,
	Alto_SI = 988
};

enum Treble
{
	Treble_DO = 1046,
	Treble_RE = 1175,
	Treble_M = 1318,
	Treble_FA = 1397,
	Treble_SO = 1568,
	Treble_LA = 1760,
	Treble_SI = 1967
};

extern unsigned int BassArray[];
extern unsigned int AltoArray[];
extern unsigned int TrebleArray[];
extern unsigned int music_little_star[][2];

void Sound(unsigned int frequency);

#endif	// __MUSIC_H__
