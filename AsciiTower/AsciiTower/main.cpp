#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "conioex.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
	// �v���O�����X�^�[�g
	setTitle();
	gameLoop();
}

void setTitle()
{
	// �R���\�[���̃^�C�g�����Z�b�g
	char title[] = TITLE;
	char *pTitle = title;
	setcaption(pTitle);
}