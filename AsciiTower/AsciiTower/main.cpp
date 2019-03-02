#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "conioex.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
	// プログラムスタート
	setTitle();
	gameLoop();
}

void setTitle()
{
	// コンソールのタイトルをセット
	char title[] = TITLE;
	char *pTitle = title;
	setcaption(pTitle);
}