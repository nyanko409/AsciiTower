#define _CRT_SECURE_NO_WARNINGS
#include "character.h"
#define CONIOEX
#include "conioex.h"
#include <stdio.h>
#include <stdlib.h>

// �O���[�o���ϐ�
character player, *pPlayer;

//�@�֐�
character* getCharacter()
{
	return pPlayer;
}

void setName()
{
	// �v���C���[������
	player.atk = 0;
	player.curHp = 0;
	player.heal = 0;
	player.hp = 0;
	player.lvl = 0;
	strcpy(player.name, "");
	pPlayer = &player;

	// ���͏���
	gotoxy(45,10);  printf("��������������������������������");
	gotoxy(45, 11); printf("��                            ��");
	gotoxy(45, 12); printf("��   ���O����͂��Ă�������   ��");
	gotoxy(45, 13); printf("��                            ��");
	gotoxy(45, 14); printf("��                            ��");
	gotoxy(45, 15); printf("��                            ��");
	gotoxy(45, 16); printf("��������������������������������");

	setcursortype(1);
	gotoxy(55, 14);
	rewind(stdin);
	scanf("%s", &pPlayer->name);
	setcursortype(0);

	while ((GetAsyncKeyState(VK_RETURN) & 0x8000));
}

void generateStats()
{
	// ���O�����ɃV�[�h�̌v�Z
	char seedString[20];

	int seedNumber = 1;
	strcpy(seedString, pPlayer->name);

	for (int i = 0; seedString[i] != '\0'; i++)
	{
		seedNumber += (seedNumber * 2) + seedString[i];
	}

	//�@�X�e�[�^�X�ݒ�
	int points = 15;
	srand(seedNumber);

	for (int x = 0; x < points; x++)
	{
		int roll = rand() % 100;
		if (roll <= 33)
			pPlayer->atk++;
		else if (roll <= 66)
			pPlayer->hp += 3;
		else
			pPlayer->heal++;
	}
	
	// �x�[�X
	if (pPlayer->atk == 0) pPlayer->atk = 1;
	if (pPlayer->hp <= 10) pPlayer->hp = 10;
	pPlayer->curHp = pPlayer->hp;
	pPlayer->lvl = 1;
}

void saveChar()
{
	// �f�[�^�̃Z�[�u
	FILE *file;
	file = fopen("_data/character.dat", "wb");
	fwrite(pPlayer, sizeof(character), 1, file);
	fclose(file);
}

bool loadChar()
{
	// �v���C���[����
	pPlayer = &player;

	// �f�[�^�̃��[�h
	FILE *file;
	file = fopen("_data/character.dat", "rb");
	if (file != NULL)
	{
		fread(pPlayer, sizeof(character), 1, file);
	}
	else return false;

	fclose(file);
	return true;
}

void deleteChar()
{
	//�@�f�[�^�폜
	remove("_data/character.dat");
}

void displayStats()
{
	// �X�e�[�^�X��\���i�f�o�b�N�v�j
	clrscr();
	printf("���O: %s\nLVL: %d\nATK: %d\nHEAL: %d\nHP: %d\n\n", pPlayer->name, pPlayer->lvl, pPlayer->atk, pPlayer->heal, pPlayer->hp);
}