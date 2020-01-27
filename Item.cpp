#include <stdio.h>
#include <math.h>
#include "Item.h"
#include "yssimplesound.h"

supportItem::supportItem()
{
	itemplayer.MakeCurrent();
	itemplayer.Start();
	GameViewWei = 54;
	GameViewHei = 42;
	rangeR = 2;
	itemType = rand() % 4;
	if (YSOK != eatitem.LoadWav("SoundTrack/eatitem.wav"))
	{
		printf("Error!  Cannot load eatitem.wav!\n");
	}
}


void supportItem::Initialize(Monster &monster, int monsterNum)
{
    
	dropNum = 1;
	for (int i = 0; i < dropNum; i++)
		if (monster.mstate == 0 && stateTrans == true)
		{
			state[i] = 1;
			stateTrans = false;
		}
}

void supportItem::getLocation(int monster_x, int monster_y)
{
    double angleInterval = 2*PI/dropNum; // angle in radian;
    for (int i=0; i<dropNum; i++)
    {
        x[i] = round(monster_x + rangeR*cos(angleInterval*i));
        y[i] = round(monster_y + rangeR*sin(angleInterval*i));
        
    }
}

void supportItem::checkView(Player &player, int monsterType)
{
    int GVx0, GVy0;
    GVx0 = player.x - GameViewWei/2;
    GVy0 = player.y - GameViewHei/2;
    
    for (int i=0; i<GameViewWei; i++)
    {
        for (int j=0; j<GameViewHei; j++)
        {
            for (int k=0; k<dropNum; k++)
            {
                if (x[k] == i+GVx0 && y[k] == j+GVy0)
                {
                    DrawSingle(monsterType, i*15, j*15, state[k]);
                }
            }
        }
    }
}


void supportItem::DrawSingle(int monsterType, int x, int y, int state)
{
    if (state == 1)
    {
        switch (monsterType)
        {
            case 1:
                png.Decode("Items/Google.png");
                itemType = 1;
                break;
            case 2:
                png.Decode("Items/Coffee.png");
                itemType = 2;
                break;
			case 3:
				png.Decode("Items/Github.png");
				itemType = 3;
				break;
			case 4:
				png.Decode("Items/Cheatsheet.png");
				itemType = 4;
				break;
        }
        png.Flip();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glRasterPos2d((double)x, (double)y);
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
    }
}


void supportItem::DrawTotal(int monsterType)
{
    for (int i=0; i<dropNum; i++)
    {
        DrawSingle(monsterType, x[i], y[i], state[i]);
    }
}

int supportItem::CheckConsume(Player &player, int ix, int iy)
{
	int relativeX = abs(ix - player.x);
	int relativeY = abs(iy - player.y);
	if (0 <= relativeX && relativeX < 2 && 0 <= relativeY && relativeY < 3)
	{
	
		return 1;
    }
    else
    {
        return 0;
    }
}

void supportItem::Comsume(Player &player, Monster &monster, int &ballnum, Ball ball[])
{
    for (int i=0; i<dropNum; i++)
    {
        if (CheckConsume(player, x[i], y[i]) == 1 && state[i] == 1)
        {
            state[i] = 0;
			itemplayer.Stop(eatitem);
			itemplayer.PlayOneShot(eatitem);
            switch (itemType)
            {
                case 1: player.hp += 1;
                    break;
				case 2: ballnum++;
					if (ballnum >= 10)
					{
						ballnum = 10;
					}
                    break;
                case 3: 
					for (int i = 0; i < ballnum; i++)
					{
						ball[i].damage++;
					}
                    break;
                case 4: player.hp += 5;
                    break;
            }
        }
    }
}

void supportItem::LucybagStart()
{
	for (int i = 0; i < 3; i++)
    {
        bagState[i] = 1;
    }
}
void supportItem::Lucybag(Player &player)
{
    int GVx0, GVy0;
    int bag_y[3];
    
    bag_y[0] = 141;
    bag_y[1] = 152;
    bag_y[2] = 163;


    GVx0 = player.x - GameViewWei/2;
    GVy0 = player.y - GameViewHei/2;
    
    // Draw luckbag;
    for (int i=0; i<GameViewWei; i++)
    {
        for (int j=0; j<GameViewHei; j++)
        {
            for (int k=0; k<3; k++)
            {
                if (31 == i+GVx0 && bag_y[k] == j+GVy0 && bagState[k] == 1)
                {
                    png.Decode("Items/Luckbag.png");
                    png.Flip();
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glRasterPos2d((double)i*15, (double)j*15);
                    glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
                    glDisable(GL_BLEND);
                }
            }
        }
    }
    
    // Check;
    for (int i=0; i<3; i++)
    {
        int relativeX = abs(31 - player.x);
        int relativeY = abs(bag_y[i] - player.y);
        if (0 <= relativeX && relativeX < 2 && 0 <= relativeY && relativeY < 3 && bagState[i] == 1)
        {
            int randNum = rand() % 4;
            bagState[i] = 0;
            switch (randNum)
            {
                case 0: player.hp ++; break;
                case 1: player.hp --; break;
                case 2: player.hp += 5; break;
                // case 3: ;break;
            }
            
        }
    }
}
