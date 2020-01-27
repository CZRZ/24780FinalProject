#ifndef MONSTER_H_IS_INCLUDED
#define MONSTER_H_IS_INCLUDED

#include <iostream>
#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include <time.h>
#include "Character.h"
#include <chrono>

class Monster :public Character
{
public:
	GLuint wtexId;
	YsRawPngDecoder weapon;
	int mstate, wstate;
	double weaponx, weapony, wvx, wvy;
	std::chrono::system_clock::time_point start;
	Monster();
	void SaveWeaponTexture();
	void DrawWeapon(int pixelwx, int pixelwy);
	bool CheckHit(int playerx, int playery);
	int Hp(bool hit);
	void timetodie(double time); //after 5 seconds, change the state of monster to 0. test use
	double timecount(std::chrono::system_clock::time_point starttime);
	void DrawMonster(int playerx, int playery);
	void Move(const char MapValue[300][300]);
	void Attack(int playerx, int playery, const char mapvalue[300][300]);
};

#endif