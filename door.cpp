#include <stdio.h>
#include <stdlib.h>
#include "door.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"

//#include "yspng.h"
//#include "yspngenc.h"

Door::Door()
{
	doorplayer.MakeCurrent();
	doorplayer.Start();
	if (YSOK != dooropensound.LoadWav("SoundTrack/dooropensound.wav"))
	{
		printf("Error!  Cannot load dooropensound.wav!\n");
	}
	doorplaystate = 1;
	state = 0;
	dooropen.Decode("MapData/dooropen.png");
	dooropen.Flip();
	doorclose.Decode("MapData/doorclose.png");
	doorclose.Flip();
}

Door::Door(int x, int y)
{
	this->x = x;
	this->y = y;
	state = 0;
	dooropen.Decode("MapData/dooropen.png");
	dooropen.Flip();
	doorclose.Decode("MapData/doorclose.png");
	doorclose.Flip();
}

void Door::control(int playerx, int playery, char mapvalueforead[300][300], char mapvalue[300][300])
{
	if ((x - playerx < 2 && playerx - x < 2) && (y - playery < 2 && playery - y < 2))
	{
		if (doorplaystate == 1)
		{
			doorplayer.Stop(dooropensound);
			doorplayer.PlayOneShot(dooropensound);
			doorplaystate = 0;
		}
		
		open();
		mapvalueforead[x][y] = '2';
		mapvalueforead[x + 1][y] = '2';
		mapvalue[x][y] = '2';
		mapvalue[x + 1][y] = '2';
	}

}

void Door::SpecialControl(Monster &monster, char mapvalueforead[300][300], char mapvalue[300][300])
{
	if (monster.mstate == 0)
	{
		open();
		mapvalueforead[x][y] = '2';
		mapvalueforead[x + 1][y] = '2';
		mapvalue[x][y] = '2';
		mapvalue[x + 1][y] = '2';
	}


}

void Door::open()
{
	state = 1;

}

void Door::close()
{
	state = 0;
}

void Door::draw(int playerX, int playerY)
{
	int GameviewWidth = 54;
	int GameviewHeight = 42;
	int GVOriginX = playerX - GameviewWidth / 2;
	int GVOriginY = playerY - GameviewHeight / 2;
	int tileWidth = 15;
	int tileLength = 15;
	for (int x = 0; x < GameviewWidth; x++)
		for (int y = 0; y < GameviewHeight; y++)//the erogodicity of x * y
		{
				if (x + GVOriginX == this->x && y + GVOriginY == this->y)
				{
					if (state == 1)
					{
						glRasterPos2i(x*tileWidth, y*tileLength);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glDrawPixels(dooropen.wid, dooropen.hei, GL_RGBA, GL_UNSIGNED_BYTE, dooropen.rgba);
						glDisable(GL_BLEND);
					}
					
					if (state == 0)
					{
						glRasterPos2i(x*tileWidth, y*tileLength);
						glDrawPixels(doorclose.wid, doorclose.hei, GL_RGBA, GL_UNSIGNED_BYTE, doorclose.rgba);

					}
				}
		}
}

Doorlist::Doorlist()
{
	NormalDoors[0].x = 140;
	NormalDoors[0].y = 151;
	NormalDoors[1].x = 132;
	NormalDoors[1].y = 270;
	NormalDoors[2].x = 128;
	NormalDoors[2].y = 231;
	NormalDoors[3].x = 118;
	NormalDoors[3].y = 90;
	NormalDoors[4].x = 172;
	NormalDoors[4].y = 40;
	NormalDoors[5].x = 90;
	NormalDoors[5].y = 270;
	NormalDoors[5].doorclose.Decode("MapData/floor.png");
	NormalDoors[5].doorclose.Flip();
	SpecialDoors[0].x = 103;
	SpecialDoors[0].y = 200;
	SpecialDoors[1].x = 225;
	SpecialDoors[1].y = 121;
	SpecialDoors[2].x = 172;
	SpecialDoors[2].y = 100;
}

void Doorlist::SpeicalControl(Monster monsters[], char mapvalueforead[300][300], char mapvalue[300][300])
{
	for (int i = 0; i < SpecialDoorNum; i++)
	{
		SpecialDoors[i].SpecialControl(monsters[i], mapvalueforead, mapvalue);
	}
}


void Doorlist::NormalControl(int playerX, int playerY, char mapvalueforead[300][300], char mapvalue[300][300])
{
	for (int i = 0; i < NormalDoorNum; i++)
	{
		NormalDoors[i].control(playerX, playerY,mapvalueforead, mapvalue);
	}
}

void Doorlist::DoorsDraw(int playerX, int playerY)
{

	for (int i = 0; i < SpecialDoorNum; i++)
	{
		SpecialDoors[i].draw(playerX, playerY);
	}
	for (int i = 0; i < NormalDoorNum; i++)
	{
		NormalDoors[i].draw(playerX, playerY);
	}
}
#pragma once
