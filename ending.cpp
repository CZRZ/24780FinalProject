#include "yssimplesound.h"
#include "yspng.h"
#include <stdio.h>
#include "Ending.h"

// ////////////////////////////
Ending::Ending()
{
	png.Decode("opening_and_ending/ending.png");
	endingplayer.MakeCurrent();
	endingplayer.Start();
	if (YSOK != endingsound.LoadWav("SoundTrack/ending.wav"))
	{
		printf("Error!  Cannot load ending.wav!\n");
	}
	png.Flip();
	r = 255;
	g = 255;
	b = 255;
	y = 600;
	x = 400;
	drawy = 200;
}

void Ending::DrawList()
{
	DrawBackground();
	Legend();
	drawy = y;
	for (int i = 0; i < 7; i++)
	{
		switch (i)
		{
		case 0: 
			strcpy(memberName, "Made by: 4am @ Pitts");
			glColor3ub(r, g, b);
			glRasterPos2i(x - 10 * 16, drawy);
			YsGlDrawFontBitmap16x20(memberName);
			break;
		case 1: 
			strcpy(memberName, "Tiecheng Wang");
			glRasterPos2i(x - 6.5 * 10, drawy);
			glColor3ub(r, g, b);
			YsGlDrawFontBitmap10x14(memberName);
			break;
		case 2: 
			strcpy(memberName, "Jiang Xiao");
			glRasterPos2i(x - 5 * 10, drawy);
			glColor3ub(r, g, b);
			YsGlDrawFontBitmap10x14(memberName);
			break;
		case 3: 
			strcpy(memberName, "Jincheng Lu");
			glRasterPos2i(x - 5.5 * 10, drawy);
			glColor3ub(r, g, b);
			YsGlDrawFontBitmap10x14(memberName);
			break;
		case 4: 
			strcpy(memberName, "Zeruizhi Cheng");
			glRasterPos2i(x - 7 * 10, drawy);
			glColor3ub(r, g, b);
			YsGlDrawFontBitmap10x14(memberName);
			break;
		case 5: 
			strcpy(memberName, "Kangchun Wang");
			glRasterPos2i(x - 6.5 * 10, drawy);
			glColor3ub(r, g, b);
			YsGlDrawFontBitmap10x14(memberName);
			break;
		case 6: 
			strcpy(memberName, "Ming Zhang");
			glRasterPos2i(x - 5 * 10, drawy);
			glColor3ub(r, g, b);
			YsGlDrawFontBitmap10x14(memberName);
			break;
		}
		drawy += 45;
	}
}

void Ending::DrawBackground()
{
	printf("%d %d\n", png.wid, png.hei);
	glRasterPos2i(0, 599);
	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
}

void Ending::Move()
{
	y += -5 * 0.25;

	if (y < -400)
	{
		endingplayer.End();
		exit(1);
	}
}

void Ending::Legend()
{
	strcpy(memberName, "Special thanks to: Soji Yamakawa");
	glColor3ub(r, g, b);
	glRasterPos2i(x - 16 * 16, y + 45 * 8);
	YsGlDrawFontBitmap16x20(memberName);

	strcpy(memberName, "Copyrights @ ALL Team Members 2019");
	glColor3ub(255, g, b);
	glRasterPos2i(x - 17 * 10, y + 45 * 9);
	YsGlDrawFontBitmap10x14(memberName);

	glEnd();
}

void Ending::Display()
{
	for (;;)
	{
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		endingplayer.PlayBackground(endingsound);

		DrawBackground();
		DrawList();
		Move();

		FsSwapBuffers();
		FsSleep(25);
	}
}