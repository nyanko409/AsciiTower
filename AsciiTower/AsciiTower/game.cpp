#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#define CONIOEX
#include "conioex.h"
#include "character.h"
#include "asciiart.h"
#include "soundManager.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �O���[�o���ϐ�
character *refPlayer;

char enemyName[20];
bool playerIsAlive, enemyIsAlive;
int enemyHp, enemyCurHp, enemyAtk, curTurn;

char sound[20];

// �֐�
void gameLoop()
{
	// ���C�����y�Đ�
	strcpy(sound, MAIN_BGM);
	playBGM(sound, true, 50 * AUDIO_MULTIPLIER);

	// ���C�����j���[
	if(!initGame()) return;

	// �ϐ��ݒ�A���y���~
	strcpy(enemyName, "");
	enemyHp = enemyCurHp = enemyAtk = curTurn = 0;
	refPlayer = getCharacter();
	playerIsAlive = true;
	enemyIsAlive = false;
	stopBGM();

	// ���C���Q�[���̃��[�v
	while (true)
	{
		// ���̓G�̐ݒ�
		updateEnemyStats();
		clrscr();

		// �������
		strcpy(sound, PREPARATION_BGM);
		playBGM(sound, true, 50 * AUDIO_MULTIPLIER);
		if (!drawTopMenu())
		{
			saveChar();
			return;
		}

		// �o�g�����y
		curTurn = 1;
		stopBGM();
		strcpy(sound, BATTLE_BGM);
		playBGM(sound, true, 50 * AUDIO_MULTIPLIER);

		// �퓬���[�v
		while (true)
		{
			//�@�퓬�X�N���[���̕\��
			updateBGM();
			int choice = drawFightScreen();
			
			// �퓬�̃��W�b�N
			if(drawFightAnimation(choice))
				break;

			curTurn++;
		}

		//�@���y��~
		stopBGM();
		stopSound();

		// �Q�[���N���A�ƃQ�[���I�[�o�[�̃`�F�b�N
		if (refPlayer->lvl > 10)
		{
			gameClearScreen();
			return;
		}
		if (!playerIsAlive)
		{
			drawGameOverScreen();
			return;
		}
	}
}

bool drawFightAnimation(int choice)
{
	int value = 0, animCount = 0;

	// �v���C���[�̍U��
	if (choice == 0)
	{
		stopSound();
		strcpy(sound, DAMAGE_SOUND);
		playSound(sound, 20 * AUDIO_MULTIPLIER);
		value = attackEnemy(refPlayer->atk);
	}
	else
	{
		stopSound();
		strcpy(sound, HEAL_SOUND);
		playSound(sound, 100 * AUDIO_MULTIPLIER);
		value = heal();
	}

	// �_���[�W�A�j���[�V�����@�G
	while (animCount < 5)
	{
		clrscr();
		gotoxy(55, 3); printf("�^�[�� %d", curTurn);
		printBattleText(value, true, false, choice);
		if (choice == 0)
		{
			printCurrentCharacter(15, 8);
			msleep(100);
			textcolor(4);
			printCurrentEnemy(80, 3);
			textcolor(15);
			msleep(100);
		}
		else
		{
			printCurrentEnemy(80, 3);
			msleep(100);
			textcolor(2);
			printCurrentCharacter(15, 8);
			textcolor(15);
			msleep(100);
		}

		animCount++;
	}

	rewind(stdin);
	getchar();
	while (GetAsyncKeyState(VK_RETURN) & 0x8000);

	if (!enemyIsAlive)
	{
		stopBGM();
		drawLevelupScreen();
		return true;
	}

	// �G�̍U��
	value = attackPlayer(enemyAtk);
	stopSound();
	strcpy(sound, DAMAGE_SOUND);
	playSound(sound, 20 * AUDIO_MULTIPLIER);

	// �_���[�W�A�j���[�V�����@�v���C���[
	animCount = 0;
	while (animCount < 5)
	{
		clrscr();
		gotoxy(55, 3); printf("�^�[�� %d", curTurn);
		printBattleText(value, false, value > (enemyAtk + curTurn / 4), false);
		printCurrentEnemy(80, 3);
		msleep(100);
		textcolor(4);
		printCurrentCharacter(15, 8);
		textcolor(15);
		msleep(100);
		animCount++;
	}

	rewind(stdin);

	getchar();
	while (GetAsyncKeyState(VK_RETURN) & 0x8000);

	if (!playerIsAlive)
	{
		return true;
	}

	return false;
}

void printBattleText(int amount, bool isPlayer, bool crit = false, bool heal = false)
{
	if (isPlayer && !heal)
	{
		gotoxy(45, 22); 
		printf("%s��", enemyName);
		textcolor(4);
		printf("%d", amount);
		textcolor(15);
		printf("�_���[�W��������!");
	}
	else if (isPlayer && heal)
	{
		gotoxy(45, 22);
		printf("%s��", refPlayer->name);
		textcolor(2);
		printf("%d", amount);
		textcolor(15);
		printf("��HP���񕜂���!");
	}
	else if (!crit)
	{
		gotoxy(50, 22); printf("%s���U�������I", enemyName);
		gotoxy(52, 23);
		textcolor(4);
		printf("%d ", amount);
		textcolor(15);
		printf("�̃_���[�W!");
	}
	else
	{
		gotoxy(43, 22); printf("%s�͖{�C���o���Ă������������I", enemyName);
		gotoxy(49, 23);
		textcolor(4);
		printf("%d ", amount);
		textcolor(15);
		printf("�_���[�W���󂯂��I");
	}
}

void gameClearScreen()
{
	clrscr();

	gotoxy(55, 15); printf("�^���[�̓G��S���|���܂���!");
	deleteChar();

	rewind(stdin);
	getchar();
}

void drawGameOverScreen()
{
	clrscr();

	// �Q�[���I�[�o�[�A�f�[�^�폜
	textcolor(4);
	gotoxy(55, 15); printf("YOU DIED");
	deleteChar();

	rewind(stdin);
	getchar();
}

void drawLevelupScreen()
{
	// ���x���グ
	refPlayer->lvl++;
	if (refPlayer->lvl > 10) return;

	stopSound();
	strcpy(sound, LVLUP_SOUND);
	playSound(sound, 20 * AUDIO_MULTIPLIER);

	int input, points = 3, posX = 50, posY = 12;
	while (true)
	{
		// �X�e�[�^�X�\��
		clrscr();
		gotoxy(50, 10); printf("�c��̃|�C���g: %d", points);
		gotoxy(55, 12); printf("HP: %d", refPlayer->hp);
		gotoxy(55, 13); printf("ATK: %d", refPlayer->atk);
		gotoxy(55, 14); printf("HEAL: %d", refPlayer->heal);

		gotoxy(posX, posY); printf("->");
		gotoxy(posX + 14, posY); printf("<-");

		input = getch();

		switch (input)
		{
		case keyUp:
			posY--;
			if (posY == 11) posY = 14;
			break;
		case keyDown:
			posY++;
			if (posY == 15) posY = 12;
			break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			while (GetAsyncKeyState(VK_RETURN) & 0x8000);

			if (posY == 12) refPlayer->hp += 3;
			if (posY == 13) refPlayer->atk += 1;
			if (posY == 14) refPlayer->heal += 1;

			// HP�񕜂��ď�����ʂ��߂�
			points--;
			if (points <= 0)
			{
				refPlayer->curHp = refPlayer->hp;
				stopSound();
				return;
			}
		}
	}
}

int heal()
{
	refPlayer->curHp += refPlayer->heal;
	if (refPlayer->curHp > refPlayer->hp)
		refPlayer->curHp = refPlayer->hp;

	return refPlayer->heal;
}

int attackEnemy(int dmg)
{
	enemyCurHp -= dmg;

	if (enemyCurHp <= 0)
		enemyIsAlive = false;

	return dmg;
}

int attackPlayer(int dmg)
{
	// �V�[�h
	srand(time(NULL));

	// �U���͂̌v�Z
	float totalDmg = dmg;
	if (rand() % 10 <= enemyCritChance * 10)
	{
		totalDmg *= enemyCritMultiplier;
	}

	totalDmg += curTurn / 4;
	
	refPlayer->curHp -= totalDmg;

	if (refPlayer->curHp <= 0)
		playerIsAlive = false;

	return totalDmg;
}

bool drawTopMenu()
{
	int input;
	int posX = 8;
	int posY = 25;

	while (true)
	{
		// �X�e�[�^�X�\��
		gotoxy(10, 5); printf("���O: %s", refPlayer->name);
		gotoxy(10, 7); printf("LVL: %d", refPlayer->lvl);
		gotoxy(10, 9); printf("HP: %d", refPlayer->hp);
		gotoxy(10, 11); printf("ATK: %d", refPlayer->atk);
		gotoxy(10, 13); printf("HEAL: %d", refPlayer->heal);

		// ���̓G
		gotoxy(90, 2); printf("%d�K: %s", refPlayer->lvl, enemyName);
		printCurrentEnemy(80, 3);

		// �I��
		gotoxy(10, 25); printf("�키");
		gotoxy(20, 25); printf("�Z�[�u���ē�����");

		// �A���[
		gotoxy(posX, posY); printf("->");

		// ���[�U�[���͂܂�
		input = getch();

		//�@�A���[�̏ꏊ�ݒ�
		switch (input)
		{
		case keyRight:
			if (posX == 18) posX = 8;
			else posX = 18;
			break;
		case keyLeft:
			if (posX == 8) posX = 18;
			else posX = 8;
			break;
		}

		//�@���͏���
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			while (GetAsyncKeyState(VK_RETURN) & 0x8000);

			clrscr();
			if (posX == 8) return true;
			else return false;
		}

		clrscr();
	}
}

int drawFightScreen()
{
	int input;
	int posX = 13, posY = 23;

	while (true)
	{
		// �L�����N�^�[�ƓG�̕\��
		printCurrentCharacter(15, 8);
		gotoxy(15, 20); printf("%s HP(%d/%d)", refPlayer->name, refPlayer->curHp, refPlayer->hp);
		printCurrentEnemy(80, 3);
		gotoxy(80, 20); printf("%s HP(%d/%d)", enemyName, enemyCurHp, enemyHp);

		// �v���C���[�̑I��
		gotoxy(15, 23); printf("�U��(%d)", refPlayer->atk);
		gotoxy(28, 23);  printf("�q�[��(%d)", refPlayer->heal);
		gotoxy(posX, posY); printf("->");
		
		//�@�I���܂�
		input = getch();

		switch (input)
		{
		case keyRight:
			if (posX == 26) posX = 13;
			else posX = 26;
			break;
		case keyLeft:
			if (posX == 13) posX = 26;
			else posX = 13;
			break;
		}

		// ���͏���
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			while (GetAsyncKeyState(VK_RETURN) & 0x8000);

			// 0 ==	�U��, 1 == �q�[��
			if (posX == 13) return 0;
			else return 1;
		}

		clrscr();
	}
}

void updateEnemyStats()
{
	setEnemyName();
	enemyIsAlive = true;

	enemyHp = 8 * refPlayer->lvl;
	enemyAtk = 1 * refPlayer->lvl;
	enemyCurHp = enemyHp;
}

void setEnemyName()
{
	if (refPlayer->lvl <= 2) strcpy(enemyName, "�I�I�J�~");
	else if (refPlayer->lvl <= 4) strcpy(enemyName, "�C���J");
	else if (refPlayer->lvl <= 6) strcpy(enemyName, "�ŃL�m�R");
	else if (refPlayer->lvl <= 8) strcpy(enemyName, "������");
	else if (refPlayer->lvl <= 10) strcpy(enemyName, "�s�J�`���E");
}

void printCurrentEnemy(int x, int y)
{
	if (refPlayer->lvl <= 2) printWolf(x, y);
	else if (refPlayer->lvl <= 4) printDolphin(x - 10, y);
	else if (refPlayer->lvl <= 6) printMushroom(x + 5, y + 1);
	else if (refPlayer->lvl <= 8) printGhost(x + 5, y + 1);
	else if (refPlayer->lvl <= 10) printPikachu(x + 7, y + 1);
}

void printCurrentCharacter(int x, int y)
{
	if (refPlayer->lvl < 3) printCharacterBaby(x, y);
	else if (refPlayer->lvl < 7) printCharacterDogbert(x, y);
	else  printCharacterGorilla(x, y);
}

bool initGame()
{
	// �J�[�T������
	setcursortype(0);

	// ���C�����j���[�̕\��
	int init = drawMainMenu();

	// �V�����n�߂�
	if (init == 0)
	{
		setupNewChar();
		return true;
	}

	// �L�����N�^�[�̃��[�h
	else if (init == 1)
	{
		if (!loadChar())
		{
			// �f�[�^�����݂��Ȃ��ꍇ�̃G���[���b�Z�[�W
			if (drawFailedLoadMenu())
			{
				setupNewChar();
				return true;
			}
			return false;
		}
		return true;
	}

	// �Q�[���I��
	else return false;
}

int drawMainMenu()
{
	int input;
	int posX = 52, posY = 14;

	while (true)
	{
		// �o�b�N�O���E���h
		printAsciiTower(10, 5);
		printAsciiTower(80, 5);
		textcolor(2);
		gotoxy(1, 27); printf("������������������������������������������������������������������������������������������������������������������������");
		gotoxy(1, 28); printf("������������������������������������������������������������������������������������������������������������������������");
		gotoxy(1, 29); printf("������������������������������������������������������������������������������������������������������������������������");
		textcolor(15);

		// ���j���[�\��
		gotoxy(55, 10); printf("%s", TITLE);
		gotoxy(55, 14); printf("�V�����n�߂�");
		gotoxy(55, 15); printf("��������");
		gotoxy(55, 16); printf("�I��");

		// draw arrow
		gotoxy(posX, posY); printf("->");

		// get user input
		input = getch();
		
		// change X/Y pos
		switch (input)
		{
			case keyUp:
			posY--;
			if (posY < 14) posY = 16;
			break;
		case keyDown:
			posY++;
			if (posY > 16) posY = 14;
			break;
		}

		// after enter press return value
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			// needed for preventing duplicate key press
			while (GetAsyncKeyState(VK_RETURN) & 0x8000);

			// 0 == new game, 1 == load game, 2 == quit game
			clrscr();
			if (posY == 14) return 0;
			if (posY == 15) return 1;
			return 2;
		}

		// refresh screen every frame
		clrscr();
	}
}

bool drawFailedLoadMenu()
{
	int input;
	int posX = 47;
	int posY = 11;

	while (true)
	{
		gotoxy(35, 8); printf("�Z�[�u�f�[�^��������܂���B�ŏ�����͂��߂܂����H");
		gotoxy(50, 11); printf("�͂�");
		gotoxy(50, 12); printf("�I��");

		gotoxy(posX, posY); printf("->");

		input = getch();

		switch (input)
		{
		case keyUp:
			posY--;
			if (posY < 11) posY = 12;
			break;
		case keyDown:
			posY++;
			if (posY > 12) posY = 11;
			break;
		}

		// ���͏���
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			while (GetAsyncKeyState(VK_RETURN) & 0x8000);

			clrscr();
			if (posY == 11) return true;
			else return false;
		}

		clrscr();
	}
}

void setupNewChar()
{
	// �V�����f�[�^�̍Ő�
	setName();
	generateStats();
	saveChar();
}
