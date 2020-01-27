#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED
#include "yssimplesound.h"
#include "yspng.h"
#include "Monster.h"

class Door
{
protected:
	int doorplaystate;
	
	YsSoundPlayer::SoundData dooropensound;

public:
	YsRawPngDecoder dooropen;
	YsRawPngDecoder doorclose;
	YsSoundPlayer doorplayer;
	int state;
	int x;
	int y;
	Door(int x, int y);
	Door();
	void control(int playerx, int playery, char mapvalueforread[300][300], char mapvalue[300][300]);
	void SpecialControl(Monster &monster, char mapvalueforead[300][300], char mapvalue[300][300]);
	void open();
	void close();
	void draw(int playerX, int playerY);
};

class Doorlist
{
protected:
	const int NormalDoorNum = 6;
	const int SpecialDoorNum = 3;
public:
	Door NormalDoors[6];

	Door SpecialDoors[3];
	Doorlist();

	void SpeicalControl(Monster monsters[], char mapvalueforead[300][300], char mapvalue[300][300]);
	void NormalControl(int playerX, int playerY, char mapvalueforead[300][300], char mapvalue[300][300]);
	void DoorsDraw(int playerX, int playerY);
};

#endif // !DOOR_H_INCLUDED


#pragma once
