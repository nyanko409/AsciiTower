#define _CRT_SECURE_NO_WARNINGS
#include "character.h"
#define CONIOEX
#include "conioex.h"
#include <stdio.h>
#include <stdlib.h>

// グローバル変数
character player, *pPlayer;

//　関数
character* getCharacter()
{
	return pPlayer;
}

void setName()
{
	// プレイヤー初期化
	player.atk = 0;
	player.curHp = 0;
	player.heal = 0;
	player.hp = 0;
	player.lvl = 0;
	strcpy(player.name, "");
	pPlayer = &player;

	// 入力処理
	gotoxy(45,10);  printf("■■■■■■■■■■■■■■■■");
	gotoxy(45, 11); printf("■                            ■");
	gotoxy(45, 12); printf("■   名前を入力してください   ■");
	gotoxy(45, 13); printf("■                            ■");
	gotoxy(45, 14); printf("■                            ■");
	gotoxy(45, 15); printf("■                            ■");
	gotoxy(45, 16); printf("■■■■■■■■■■■■■■■■");

	setcursortype(1);
	gotoxy(55, 14);
	rewind(stdin);
	scanf("%s", &pPlayer->name);
	setcursortype(0);

	while ((GetAsyncKeyState(VK_RETURN) & 0x8000));
}

void generateStats()
{
	// 名前を元にシードの計算
	char seedString[20];

	int seedNumber = 1;
	strcpy(seedString, pPlayer->name);

	for (int i = 0; seedString[i] != '\0'; i++)
	{
		seedNumber += (seedNumber * 2) + seedString[i];
	}

	//　ステータス設定
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
	
	// ベース
	if (pPlayer->atk == 0) pPlayer->atk = 1;
	if (pPlayer->hp <= 10) pPlayer->hp = 10;
	pPlayer->curHp = pPlayer->hp;
	pPlayer->lvl = 1;
}

void saveChar()
{
	// データのセーブ
	FILE *file;
	file = fopen("_data/character.dat", "wb");
	fwrite(pPlayer, sizeof(character), 1, file);
	fclose(file);
}

bool loadChar()
{
	// プレイヤー初期
	pPlayer = &player;

	// データのロード
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
	//　データ削除
	remove("_data/character.dat");
}

void displayStats()
{
	// ステータスを表示（デバック要）
	clrscr();
	printf("名前: %s\nLVL: %d\nATK: %d\nHEAL: %d\nHP: %d\n\n", pPlayer->name, pPlayer->lvl, pPlayer->atk, pPlayer->heal, pPlayer->hp);
}