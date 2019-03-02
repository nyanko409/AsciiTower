#ifndef _CHARACTER_H_
#define _CHARACTER_H_

// プライヤー構造体
struct character
{
	char name[20];
	int lvl;
	int hp;
	int curHp;
	int atk;
	int heal;
};

// 関数宣言
character* getCharacter();
void setName();
void generateStats();
void displayStats();
void saveChar();
bool loadChar();
void deleteChar();

#endif