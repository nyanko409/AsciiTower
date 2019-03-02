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

// グローバル変数
character *refPlayer;

char enemyName[20];
bool playerIsAlive, enemyIsAlive;
int enemyHp, enemyCurHp, enemyAtk, curTurn;

char sound[20];

// 関数
void gameLoop()
{
	// メイン音楽再生
	strcpy(sound, MAIN_BGM);
	playBGM(sound, true, 50 * AUDIO_MULTIPLIER);

	// メインメニュー
	if(!initGame()) return;

	// 変数設定、音楽を停止
	strcpy(enemyName, "");
	enemyHp = enemyCurHp = enemyAtk = curTurn = 0;
	refPlayer = getCharacter();
	playerIsAlive = true;
	enemyIsAlive = false;
	stopBGM();

	// メインゲームのループ
	while (true)
	{
		// 次の敵の設定
		updateEnemyStats();
		clrscr();

		// 準備画面
		strcpy(sound, PREPARATION_BGM);
		playBGM(sound, true, 50 * AUDIO_MULTIPLIER);
		if (!drawTopMenu())
		{
			saveChar();
			return;
		}

		// バトル音楽
		curTurn = 1;
		stopBGM();
		strcpy(sound, BATTLE_BGM);
		playBGM(sound, true, 50 * AUDIO_MULTIPLIER);

		// 戦闘ループ
		while (true)
		{
			//　戦闘スクリーンの表示
			updateBGM();
			int choice = drawFightScreen();
			
			// 戦闘のロジック
			if(drawFightAnimation(choice))
				break;

			curTurn++;
		}

		//　音楽停止
		stopBGM();
		stopSound();

		// ゲームクリアとゲームオーバーのチェック
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

	// プレイヤーの攻撃
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

	// ダメージアニメーション　敵
	while (animCount < 5)
	{
		clrscr();
		gotoxy(55, 3); printf("ターン %d", curTurn);
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

	// 敵の攻撃
	value = attackPlayer(enemyAtk);
	stopSound();
	strcpy(sound, DAMAGE_SOUND);
	playSound(sound, 20 * AUDIO_MULTIPLIER);

	// ダメージアニメーション　プレイヤー
	animCount = 0;
	while (animCount < 5)
	{
		clrscr();
		gotoxy(55, 3); printf("ターン %d", curTurn);
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
		printf("%sは", enemyName);
		textcolor(4);
		printf("%d", amount);
		textcolor(15);
		printf("ダメージを喰らった!");
	}
	else if (isPlayer && heal)
	{
		gotoxy(45, 22);
		printf("%sは", refPlayer->name);
		textcolor(2);
		printf("%d", amount);
		textcolor(15);
		printf("のHPを回復した!");
	}
	else if (!crit)
	{
		gotoxy(50, 22); printf("%sが攻撃した！", enemyName);
		gotoxy(52, 23);
		textcolor(4);
		printf("%d ", amount);
		textcolor(15);
		printf("のダメージ!");
	}
	else
	{
		gotoxy(43, 22); printf("%sは本気を出してこうげきした！", enemyName);
		gotoxy(49, 23);
		textcolor(4);
		printf("%d ", amount);
		textcolor(15);
		printf("ダメージを受けた！");
	}
}

void gameClearScreen()
{
	clrscr();

	gotoxy(55, 15); printf("タワーの敵を全員倒しました!");
	deleteChar();

	rewind(stdin);
	getchar();
}

void drawGameOverScreen()
{
	clrscr();

	// ゲームオーバー、データ削除
	textcolor(4);
	gotoxy(55, 15); printf("YOU DIED");
	deleteChar();

	rewind(stdin);
	getchar();
}

void drawLevelupScreen()
{
	// レベル上げ
	refPlayer->lvl++;
	if (refPlayer->lvl > 10) return;

	stopSound();
	strcpy(sound, LVLUP_SOUND);
	playSound(sound, 20 * AUDIO_MULTIPLIER);

	int input, points = 3, posX = 50, posY = 12;
	while (true)
	{
		// ステータス表示
		clrscr();
		gotoxy(50, 10); printf("残りのポイント: %d", points);
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

			// HP回復して準備画面え戻る
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
	// シード
	srand(time(NULL));

	// 攻撃力の計算
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
		// ステータス表示
		gotoxy(10, 5); printf("名前: %s", refPlayer->name);
		gotoxy(10, 7); printf("LVL: %d", refPlayer->lvl);
		gotoxy(10, 9); printf("HP: %d", refPlayer->hp);
		gotoxy(10, 11); printf("ATK: %d", refPlayer->atk);
		gotoxy(10, 13); printf("HEAL: %d", refPlayer->heal);

		// 次の敵
		gotoxy(90, 2); printf("%d階: %s", refPlayer->lvl, enemyName);
		printCurrentEnemy(80, 3);

		// 選択
		gotoxy(10, 25); printf("戦う");
		gotoxy(20, 25); printf("セーブして逃げる");

		// アロー
		gotoxy(posX, posY); printf("->");

		// ユーザー入力まち
		input = getch();

		//　アローの場所設定
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

		//　入力処理
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
		// キャラクターと敵の表示
		printCurrentCharacter(15, 8);
		gotoxy(15, 20); printf("%s HP(%d/%d)", refPlayer->name, refPlayer->curHp, refPlayer->hp);
		printCurrentEnemy(80, 3);
		gotoxy(80, 20); printf("%s HP(%d/%d)", enemyName, enemyCurHp, enemyHp);

		// プレイヤーの選択
		gotoxy(15, 23); printf("攻撃(%d)", refPlayer->atk);
		gotoxy(28, 23);  printf("ヒール(%d)", refPlayer->heal);
		gotoxy(posX, posY); printf("->");
		
		//　選択まち
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

		// 入力処理
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			while (GetAsyncKeyState(VK_RETURN) & 0x8000);

			// 0 ==	攻撃, 1 == ヒール
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
	if (refPlayer->lvl <= 2) strcpy(enemyName, "オオカミ");
	else if (refPlayer->lvl <= 4) strcpy(enemyName, "イルカ");
	else if (refPlayer->lvl <= 6) strcpy(enemyName, "毒キノコ");
	else if (refPlayer->lvl <= 8) strcpy(enemyName, "お化け");
	else if (refPlayer->lvl <= 10) strcpy(enemyName, "ピカチュウ");
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
	// カーサを消す
	setcursortype(0);

	// メインメニューの表示
	int init = drawMainMenu();

	// 新しく始める
	if (init == 0)
	{
		setupNewChar();
		return true;
	}

	// キャラクターのロード
	else if (init == 1)
	{
		if (!loadChar())
		{
			// データが存在しない場合のエラーメッセージ
			if (drawFailedLoadMenu())
			{
				setupNewChar();
				return true;
			}
			return false;
		}
		return true;
	}

	// ゲーム終了
	else return false;
}

int drawMainMenu()
{
	int input;
	int posX = 52, posY = 14;

	while (true)
	{
		// バックグラウンド
		printAsciiTower(10, 5);
		printAsciiTower(80, 5);
		textcolor(2);
		gotoxy(1, 27); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(1, 28); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(1, 29); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		textcolor(15);

		// メニュー表示
		gotoxy(55, 10); printf("%s", TITLE);
		gotoxy(55, 14); printf("新しく始める");
		gotoxy(55, 15); printf("続きから");
		gotoxy(55, 16); printf("終了");

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
		gotoxy(35, 8); printf("セーブデータが見つかりません。最初からはじめますか？");
		gotoxy(50, 11); printf("はい");
		gotoxy(50, 12); printf("終了");

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

		// 入力処理
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
	// 新しいデータの最成
	setName();
	generateStats();
	saveChar();
}
