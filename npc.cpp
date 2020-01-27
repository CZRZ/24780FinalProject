#include "npc.h"
#include "ysglfontdata.h"
#include "fssimplewindow.h"


void NPC::dialogue(int playerX, int playerY)
{
	//draw black background
	//draw character
	//draw dialogue
	if (playerX - x < 2 && x - playerX < 2 && playerY - y < 2 && y - playerY < 2)
	{
		if (FsGetKeyState(FSKEY_SPACE) != 0)
		{
			state = 1;
		}
	}
	else
		{
			state = 0;
		}

		if (state == 1)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_QUADS);
			glVertex2d(0, 400);
			glVertex2d(800, 400);
			glVertex2d(800, 600);
			glVertex2d(0, 600);//draw black background
			glEnd();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(0, 599);
			glDrawPixels(NPCchracter.wid, NPCchracter.hei, GL_RGBA, GL_UNSIGNED_BYTE, NPCchracter.rgba);
			glDisable(GL_BLEND);
			glColor3ub(255, 255, 255);
			glRasterPos2i(300, 450);
			YsGlDrawFontBitmap16x20(dialogueWordsLine1);
			glRasterPos2i(300, 500);
			YsGlDrawFontBitmap16x20(dialogueWordsLine2);
			glRasterPos2i(300, 550);
			YsGlDrawFontBitmap16x20(dialogueWordsLine3);
		}
}

void NPC::draw(int playerX, int playerY)
{
	int GVX = playerX - GameviewWidth / 2;
	int GVY = playerY - GameviewHeight / 2;

	for (int i = 0; i < GameviewWidth; i++)
		for (int j = 0; j < GameviewHeight; j++)
		{
			if (i + GVX == this->x && j + GVY == this->y)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glRasterPos2i(i*tileWidth, j*tileLength);
				glDrawPixels(NPCpng.wid, NPCpng.hei, GL_RGBA, GL_UNSIGNED_BYTE, NPCpng.rgba);
				glDisable(GL_BLEND);
			}
		}
}

NPClist::NPClist()
{
	npcs[0].x = 117;
	npcs[0].y = 274;
	npcs[0].NPCpng.Decode("NPCpngs/npc1.png");
	npcs[0].NPCpng.Flip();
	npcs[0].NPCchracter.Decode("NPCpngs/npc1character.png");
	npcs[0].NPCchracter.Flip();
	strcpy(npcs[0].dialogueWordsLine1, "Welcome to CMU");
	strcpy(npcs[0].dialogueWordsLine2, "You will suffer ");
	//strcpy(npcs[0].dialogueWordsLine3, "To enter next room, you have to defeat Quiz");
	strcpy(npcs[0].dialogueWordsLine3, "Defeat quiz to continue");
	npcs[1].x = 90;
	npcs[1].y = 205;
	npcs[1].NPCpng.Decode("NPCpngs/npc1.png");
	npcs[1].NPCpng.Flip();
	npcs[1].NPCchracter.Decode("NPCpngs/npc1character.png");
	npcs[1].NPCchracter.Flip();
	strcpy(npcs[1].dialogueWordsLine1, "Midterm is waiting for you");
	strcpy(npcs[1].dialogueWordsLine2, "Midterm is not easy to defeat");
	strcpy(npcs[1].dialogueWordsLine3, "You should be fully prepared");
	npcs[2].x = 107;
	npcs[2].y = 95;
	npcs[2].NPCpng.Decode("NPCpngs/npc1.png");
	npcs[2].NPCpng.Flip();
	npcs[2].NPCchracter.Decode("NPCpngs/npc1character.png");
	npcs[2].NPCchracter.Flip();
	strcpy(npcs[2].dialogueWordsLine1, "The last boss is Final");
	strcpy(npcs[2].dialogueWordsLine2, "You are the bravest warrior");
	strcpy(npcs[2].dialogueWordsLine3, "Don't be PANIC");
	npcs[3].x = 182;
	npcs[3].y = 56;
	npcs[3].NPCpng.Decode("NPCpngs/npc1.png");
	npcs[3].NPCpng.Flip();
	npcs[3].NPCchracter.Decode("NPCpngs/npc1character.png");
	npcs[3].NPCchracter.Flip();
	strcpy(npcs[3].dialogueWordsLine1, "YOU SURVIVED");
	strcpy(npcs[3].dialogueWordsLine2, "ENJOY YOUR");
	strcpy(npcs[3].dialogueWordsLine3, "WINTER VACATION");
}

void NPClist::drawlist(int playerX, int playerY)
{
	for (int i = 0; i < 4; i++)
	{
		npcs[i].draw(playerX, playerY);
		npcs[i].dialogue(playerX, playerY);
	}
}
