#ifndef MAP_H_IS_INCLUDED
#define MAP_H_IS_INCLUDED
#include "yssimplesound.h"
#include <stdio.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include "player.h"
#include "Monster.h"


class tacticalMap
{
protected:

	YsRawPngDecoder rawmap;
	int windowWidth;
	int windowHeight;

public:
	tacticalMap();
	void draw(int playerX, int playerY);
};


class Map
{
protected:
	int mapWidth;
	int mapHeight;
	int GameviewWidth;
	int GameviewHeight;
	double tileWidth;  //double for offset
	double tileLength;
	YsSoundPlayer::SoundData ingamebgm;
	YsRawPngDecoder tacMap;
	YsRawPngDecoder Floor; // 1 and 2, black and green
	YsRawPngDecoder WallTopBottom; // 3 Yellow
	YsRawPngDecoder WallsideLeft; // 4 blue
	YsRawPngDecoder WallsideRight; // 5 purple
	YsRawPngDecoder Treasure; // items, 6 
	YsRawPngDecoder holes; // 7 Red
	YsRawPngDecoder grass;
	//YsSoundPlayer::SoundData ingamebgm;
	void readMapdata();
	void loadTexture();
	void Holeallocation();

public:
	YsSoundPlayer mapplayer;

	char mapValue[300][300];
	char mapvalueforread[300][300];
	Map();
	void drawMap(Player &player);
	void basicGameview(int playerX, int playerY);
	//void upperGameview(int playerX, int playerY, Monster monster[]);
	//void GameView(int playerX, int playerY);
	void drawTacMap(int playerX, int playerY);
	bool locationCheck(int playerX, int playerY);
};

#endif
