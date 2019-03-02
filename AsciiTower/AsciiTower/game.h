#ifndef _GAME_H_
#define _GAME_H_

// ゲームタイトル
#define TITLE "ASCII タワー"

// アローキー
#define keyUp		72
#define keyDown		80
#define keyLeft		75
#define keyRight	77

// 敵のバランス設定
#define enemyCritChance 0.1f
#define enemyCritMultiplier 2

// 関数宣言
bool drawFightAnimation(int);
void printBattleText(int, bool, bool, bool);
void gameClearScreen();
void drawLevelupScreen();
void drawGameOverScreen();
void gameLoop();
bool drawTopMenu();
int drawFightScreen();
void updateEnemyStats();
void setEnemyName();
void printCurrentEnemy(int, int);
void printCurrentCharacter(int, int);
int attackEnemy(int);
int attackPlayer(int);
int heal();
bool initGame();
int drawMainMenu();
bool drawFailedLoadMenu();
void setupNewChar();

#endif