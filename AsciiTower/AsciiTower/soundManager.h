#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

// サウンドファイル
#define MAIN_BGM "_sfx/main_bgm.wav"
#define PREPARATION_BGM "_sfx/preparation_bgm.wav"
#define BATTLE_BGM "_sfx/battle_bgm.wav"
#define DAMAGE_SOUND "_sfx/damage_sound.wav"
#define HEAL_SOUND "_sfx/heal_sound.wav"
#define LVLUP_SOUND "_sfx/lvlup_sound.wav"

// サウンド管理
#define AUDIO_MULTIPLIER 1

// 関数宣言
void playBGM(char *, bool, int);
void playSound(char *, int);
void stopBGM();
void stopSound();
void updateBGM();

#endif