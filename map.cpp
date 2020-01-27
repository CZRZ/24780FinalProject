#include <stdio.h>
#include <stdlib.h>
#include "yssimplesound.h"
#include "player.h"
#include "yssimplesound.h"
#include "map.h"

#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "Monster.h"


Map::Map()
{
	mapplayer.MakeCurrent();
	mapplayer.Start();
	if (YSOK != ingamebgm.LoadWav("SoundTrack/ingamebgm.wav"))
	{
		printf("Error!  Cannot load ingamebgm.wav!\n");
	}
	mapWidth = 300;
	mapHeight = 300;
	GameviewWidth = 54;
	GameviewHeight = 42;
	tileWidth = 15;
	tileLength = 15;
	loadTexture();
	readMapdata();
	Holeallocation();
}

void Map::loadTexture()
{
	tacMap.Decode("MapData/tacMap.png");
	tacMap.Flip();
	Floor.Decode("MapData/floor.png");
	WallTopBottom.Decode("MapData/walltopbot.png");
	WallTopBottom.Flip();
	WallsideLeft.Decode("MapData/wallleft.png");
	WallsideRight.Decode("MapData/wallright.png");
	holes.Decode("MapData/hole.png");
	grass.Decode("MapData/grass.png");
	//if (YSOK != ingamebgm.LoadWav("SoundTrack/ingamebgm.wav"))
	//{
	//	printf("Error!  Cannot load ingamebgm.wav!\n");
	//}
}

void Map::readMapdata()
{
	int column = 0;
	int row = 0;
	char buf[310];
	char *Fname = "MapData/mapdata.txt";
	int j = 0;
	FILE *fp;
	fp = fopen(Fname, "r");
	while (nullptr != fgets(buf, 309, fp))
	{
		for (int i = 0; buf[i] != '\n'; i++)
		{
			mapValue[i][j] = buf[i];
			mapvalueforread[i][j] = buf[i];
		}
		j++;
	}
	fclose(fp);
}

void Map::Holeallocation()
{
	const int holeNum = 50;
	int holeX[holeNum];
	int holeY[holeNum];

	for (int i = 0; i < holeNum; )
	{
		holeX[i] = rand() % 300;
		holeY[i] = rand() % 300;
		if (mapValue[holeX[i]][holeY[i]] == '1')
		{
			mapValue[holeX[i]][holeY[i]] = '7';
			i++;
		}
	}
}


void Map::basicGameview(int playerX, int playerY)
{
	int GVOriginX, GVOriginY;

	GVOriginX = playerX - GameviewWidth / 2 ; //the upper left corner is (0, 0)
	GVOriginY = playerY - GameviewHeight / 2 ;

	for (int x = 0; x < GameviewWidth; x++)
		for (int y = 0; y < GameviewHeight; y++)//the erogodicity of x * y
		{
			if (mapValue[x + GVOriginX][y + GVOriginY] == '0') //find this point at mapvalue, check if this place is a reachable place
			{
				//draw the Floor in the specified point
				glRasterPos2i(x*tileWidth, y*tileLength);
				glDrawPixels(grass.wid, grass.hei, GL_RGBA, GL_UNSIGNED_BYTE, grass.rgba);
			}
			if (mapValue[x + GVOriginX][y + GVOriginY] == '1' || mapValue[x + GVOriginX][y + GVOriginY] == '2') //find this point at mapvalue, check if this place is a reachable place
			{
				//draw the Floor in the specified point
				glRasterPos2i(x*tileWidth, y*tileLength);
				glDrawPixels(Floor.wid, Floor.hei, GL_RGBA, GL_UNSIGNED_BYTE, Floor.rgba);
			}

			if (mapValue[x + GVOriginX][y + GVOriginY] == '3')
			{
				glRasterPos2i(x*tileWidth, y*tileLength);
				glDrawPixels(WallTopBottom.wid, WallTopBottom.hei, GL_RGBA, GL_UNSIGNED_BYTE, WallTopBottom.rgba);
			}

			if (mapValue[x + GVOriginX][y + GVOriginY] == '4')
			{
				glRasterPos2i(x*tileWidth, y*tileLength);
				glDrawPixels(WallsideLeft.wid, WallsideLeft.hei, GL_RGBA, GL_UNSIGNED_BYTE, WallsideLeft.rgba);
			}

			if (mapValue[x + GVOriginX][y + GVOriginY] == '5')
			{
				glRasterPos2i(x*tileWidth, y*tileLength);
				glDrawPixels(WallsideRight.wid, WallsideRight.hei, GL_RGBA, GL_UNSIGNED_BYTE, WallsideRight.rgba);
			}

			if (mapValue[x + GVOriginX][y + GVOriginY] == '7')
			{
				glRasterPos2i(x*tileWidth, y*tileLength);
				glDrawPixels(holes.wid, holes.hei, GL_RGBA, GL_UNSIGNED_BYTE, holes.rgba);
			}

		}
}

void Map::drawTacMap(int playerX, int playerY)
{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2i(0, 599);
		glDrawPixels(tacMap.wid, tacMap.hei, GL_RGBA, GL_UNSIGNED_BYTE, tacMap.rgba);
		glDisable(GL_BLEND);

		double x = playerX * 175 /300;
		double y = 601 - tacMap.hei + playerY * 175 / 300;

		glColor3ub(255, 0, 0);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i<360; i += 30)
		{
			double a = (double) i * 3.1415926535 / 180.0;
			double s = sin(a);
			double c = cos(a);
			glVertex2d(x + c * 5, y + s * 5);
		}
		glEnd();
}





void Map::drawMap(Player &player)
{
	basicGameview(player.x, player.y);
	drawTacMap(player.x, player.y);
	mapplayer.PlayBackground(ingamebgm);

}