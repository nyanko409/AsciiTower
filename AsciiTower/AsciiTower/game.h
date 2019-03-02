#ifndef _GAME_H_
#define _GAME_H_

// �Q�[���^�C�g��
#define TITLE "ASCII �^���["

// �A���[�L�[
#define keyUp		72
#define keyDown		80
#define keyLeft		75
#define keyRight	77

// �G�̃o�����X�ݒ�
#define enemyCritChance 0.1f
#define enemyCritMultiplier 2

// �֐��錾
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