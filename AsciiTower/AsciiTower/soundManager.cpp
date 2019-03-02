#define _CRT_SECURE_NO_WARNINGS
#include "soundManager.h"
#define CONIOEX
#include "conioex.h"
#include <stdio.h>
#include <string.h>

//�@�O���[�o���ϐ�
int bgmHandle = 0, soundHandle = 0;

//�@�֐�
void playBGM(char *file, bool repeat, int volume)
{
	if (bgmHandle == 0)
	{
		bgmHandle = opensound(file);
		setvolume(bgmHandle, volume);
	}

	playsound(bgmHandle, repeat);
}

void stopBGM()
{
	closesound(bgmHandle);
	bgmHandle = 0;
}

void playSound(char *file, int volume)
{
	if (soundHandle == 0)
	{
		soundHandle = opensound(file);
		setvolume(soundHandle, volume);
	}

	playsound(soundHandle, false);
}

void stopSound()
{
	closesound(soundHandle);
	soundHandle = 0;
}

void updateBGM()
{
	updatesound(bgmHandle);
}