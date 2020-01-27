#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "yssimplesound.h"
#include "fssimplewindow.h"
#include <stdio.h>
#include "player.h"
#include "Monster.h"

class Ball {
public:
	YsSoundPlayer ballplayer;
	YsSoundPlayer::SoundData ballfire;
	YsSoundPlayer::SoundData monsterdie;
	YsSoundPlayer::SoundData monstergethit;
	double x, y;
	double vx, vy;
	double vrate;
	int state;
	int damage;
	GLuint btexId;
	YsRawPngDecoder bpng;
	Ball();
	void SaveTexture();
	void Draw(double pixelwx, double pixelwy);
	void Fire(Player &player, const char mapvalue[300][300]);
	void CheckFire(Player &player, const char mapvalue[300][300], int mx, int my);
	void CheckHitMonster(Monster &monster, int &ballnum);
};

class Dart {//it is a dart that can hit monster then bounce to another random diretion and player can fetch it
public:
	double x, y;
	double vx, vy;
	int state;//0 hit wall;1 after 1st thrown;2 after 1st bounce;3 fetched in hand;4 enjoy mode thrown;5 enjoy mode bounce
	GLuint btexId1;
	GLuint btexId2;
	YsSoundPlayer dartplayer;
	YsSoundPlayer::SoundData dartfire;
	YsSoundPlayer::SoundData monstergethit;
	YsSoundPlayer::SoundData monsterdie;
	YsRawPngDecoder png1;
	YsRawPngDecoder png2;
	Dart();
	void SaveTexture1();
	void SaveTexture2();
	void Draw1(double pixelwx, double pixelwy);
	void Draw2(double pixelwx, double pixelwy);
	void Fire(Player &player, const char mapvalue[300][300]);
	void CheckDartHitMonster(Monster &monster);
	void CheckGetByPlayer(Player &player);
};

#endif // !WEAPON_H_INCLUDED