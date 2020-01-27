#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED
//#include "yssimplesound.h"
#include <stdio.h>
#include "yspng.h"
class NPC
{
protected:
	int mapWidth = 300;
	int mapHeight = 300;
	int GameviewWidth = 54;
	int GameviewHeight = 42;
	int tileWidth = 15;
	int tileLength = 15;
	int state = 0;
public:
	YsRawPngDecoder NPCpng;
	YsRawPngDecoder NPCchracter;
	int x;
	int y;
	char dialogueWordsLine1[256];
	char dialogueWordsLine2[256];
	char dialogueWordsLine3[256];
	void dialogue(int playerX, int playerY);
	void draw(int playerX, int playerY);
};

class NPClist
{
public:
	NPC npcs[4];
	NPClist();
	void drawlist(int playerX, int playerY);
};

#endif 
