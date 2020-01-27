#include "yssimplesound.h"

#include "weapon.h"
#include <stdio.h>
#include "yspng.h"
#include "yspngenc.h"
#include "math.h"

Ball::Ball()
{
	ballplayer.MakeCurrent();
	ballplayer.Start();
	if (YSOK != ballfire.LoadWav("SoundTrack/ballfire.wav"))
	{
		printf("Error!  Cannot load ballfire.wav!\n");
	}
	if (YSOK != monstergethit.LoadWav("SoundTrack/monstergethit.wav"))
	{
		printf("Error!  Cannot load monstergethit.wav!\n");
	}
	if (YSOK != monsterdie.LoadWav("SoundTrack/monsterdie.wav"))
	{
		printf("Error!  Cannot load monsterdie.wav!\n");
	}

	bpng.Decode("character_and_weapon/weapon_m2.png");
	bpng.Flip();
	SaveTexture();
	state = 0;
	x = 0;
	y = 0;
	vx = 1;
	vy = 1;
	vrate = 1;
	damage = 1;
}

void Ball::SaveTexture()
{
	glGenTextures(1, &btexId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, btexId);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		bpng.wid,
		bpng.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		bpng.rgba);
}

void Ball::Draw(double pixelwx, double pixelwy)
{
	const double PI = 3.1415926;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, btexId);

	glBegin(GL_QUADS);

	double tmp = sqrt(pow(bpng.hei, 2) + pow(bpng.wid, 2)) / 4;
	double angle = atan((double)bpng.hei / (double)bpng.wid) * 180 / PI;

	glTexCoord2d(0.0, 0.0);
	glVertex2d(pixelwx + tmp * cos((180 + angle) * PI / 180), pixelwy - tmp * sin((180 + angle) * PI / 180));

	glTexCoord2d(1.0, 0.0);
	glVertex2d(pixelwx + tmp * cos((360 - angle) * PI / 180), pixelwy - tmp * sin((360 - angle) * PI / 180));

	glTexCoord2d(1.0, 1.0);
	glVertex2d(pixelwx + tmp * cos((angle)* PI / 180), pixelwy - tmp * sin((angle)* PI / 180));

	glTexCoord2d(0.0, 1.0);
	glVertex2d(pixelwx + tmp * cos((180 - angle) * PI / 180), pixelwy - tmp * sin((180 - angle) * PI / 180));

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Ball::Fire(Player &player, const char mapvalue[300][300])
{
	if (state == 1)
	{
		Draw((x - (player.x - 27)) * 15, (y - (player.y - 20)) * 15);
		x += vx;
		y += vy;
	}
	if (mapvalue[(int)x][(int)y] == '0')
	{
		state = 0;
		return;
	}
	if (mapvalue[(int)x + 1][(int)y] == '4' || mapvalue[(int)x - 1][(int)y] == '4' ||
		mapvalue[(int)x][(int)y + 1] == '3' || mapvalue[(int)x][(int)y - 1] == '3' ||
		mapvalue[(int)x + 1][(int)y] == '5' || mapvalue[(int)x - 1][(int)y] == '5')
	{
		state = 0;
		return;
	}
	else if (mapvalue[(int)x - 2][(int)y] == '4' || mapvalue[(int)x + 2][(int)y] == '5')
	{
		state = 0;
		return;
	}
	else if (mapvalue[(int)x - 2][(int)y - 1] == '4' || mapvalue[(int)x + 2][(int)y - 1] == '4' ||
		mapvalue[(int)x + 2][(int)y + 2] == '4' || mapvalue[(int)x - 2][(int)y + 2] == '4' ||
		mapvalue[(int)x - 1][(int)y - 1] == '5' || mapvalue[(int)x + 1][(int)y - 1] == '5' ||
		mapvalue[(int)x + 1][(int)y + 2] == '5' || mapvalue[(int)x - 1][(int)y + 2] == '5' ||
		mapvalue[(int)x - 2][(int)y - 1] == '3' || mapvalue[(int)x + 2][(int)y - 1] == '3' ||
		mapvalue[(int)x + 2][(int)y + 1] == '3' || mapvalue[(int)x - 2][(int)y + 1] == '3')
	{
		state = 0;
		return;
	}
}

void Ball::CheckFire(Player &player, const char mapvalue[300][300], int mx, int my)
{
	if (state == 0) {
		ballplayer.Stop(ballfire);
		ballplayer.PlayOneShot(ballfire);
		x = (double)player.x;
		y = (double)player.y;
		vx = vrate*(mx - 400) / sqrt(pow((mx - 400), 2) + pow((my - 300), 2));
		vy = vrate*(my - 300) / sqrt(pow((mx - 400), 2) + pow((my - 300), 2));
		state = 1;
	}
}

void Ball::CheckHitMonster(Monster &monster, int &ballnum)
{
	if (monster.mstate == 0)
	{
		return;
	}
	int relativeX, relativeY;
	relativeX = abs(monster.x - x);
	relativeY = abs(monster.y - y);
	if (0 <= relativeX && relativeX < 2 && 0 <= relativeY && relativeY < 3 && state == 1)
	{
		state = 0;
		monster.hp -= damage;
		ballplayer.Stop(monstergethit);
		ballplayer.PlayOneShot(monstergethit);
		if (monster.hp <= 0)
		{
			//ballnum++;
			//if (ballnum >= 10)
			//{
			//	ballnum = 10;
			//}
			monster.mstate = 0;
			ballplayer.Stop(monsterdie);
			ballplayer.PlayOneShot(monsterdie);
		}
	}
}

Dart::Dart()
{
	dartplayer.MakeCurrent();
	dartplayer.Start();
	if (YSOK != dartfire.LoadWav("SoundTrack/dartfire.wav"))
	{
		printf("Error!  Cannot load dartfire.wav!\n");
	}
	if (YSOK != monstergethit.LoadWav("SoundTrack/monstergethit.wav"))
	{
		printf("Error!  Cannot load monstergethit.wav!\n");
	}
	if (YSOK != monsterdie.LoadWav("SoundTrack/monsterdie.wav"))
	{
		printf("Error!  Cannot load monsterdie.wav!\n");
	}

	state = 0;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	png1.Decode("character_and_weapon/weapon3_1.png");
	png2.Decode("character_and_weapon/weapon3_2.png");
	png1.Flip();
	png2.Flip();
	SaveTexture1();
	SaveTexture2();
}

void Dart::SaveTexture1()
{
	glGenTextures(1, &btexId1);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, btexId1);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		png1.wid,
		png1.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png1.rgba);
}

void Dart::SaveTexture2()
{
	glGenTextures(1, &btexId2);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, btexId2);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		png2.wid,
		png2.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png2.rgba);
}

void Dart::Draw1(double pixelwx, double pixelwy)
{
	const double PI = 3.1415926;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, btexId1);

	glBegin(GL_QUADS);

	double tmp = sqrt(pow(png1.hei, 2) + pow(png1.wid, 2)) / 4;
	double angle = atan((double)png1.hei / (double)png1.wid) * 180 / PI;

	glTexCoord2d(0.0, 0.0);
	glVertex2d(pixelwx + tmp * cos((180 + angle) * PI / 180), pixelwy - tmp * sin((180 + angle) * PI / 180));

	glTexCoord2d(1.0, 0.0);
	glVertex2d(pixelwx + tmp * cos((360 - angle) * PI / 180), pixelwy - tmp * sin((360 - angle) * PI / 180));

	glTexCoord2d(1.0, 1.0);
	glVertex2d(pixelwx + tmp * cos((angle)* PI / 180), pixelwy - tmp * sin((angle)* PI / 180));

	glTexCoord2d(0.0, 1.0);
	glVertex2d(pixelwx + tmp * cos((180 - angle) * PI / 180), pixelwy - tmp * sin((180 - angle) * PI / 180));

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Dart::Draw2(double pixelwx, double pixelwy)
{
	const double PI = 3.1415926;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, btexId2);

	glBegin(GL_QUADS);

	double tmp = sqrt(pow(png2.hei, 2) + pow(png2.wid, 2)) / 4;
	double angle = atan((double)png2.hei / (double)png2.wid) * 180 / PI;

	glTexCoord2d(0.0, 0.0);
	glVertex2d(pixelwx + tmp * cos((180 + angle) * PI / 180), pixelwy - tmp * sin((180 + angle) * PI / 180));

	glTexCoord2d(1.0, 0.0);
	glVertex2d(pixelwx + tmp * cos((360 - angle) * PI / 180), pixelwy - tmp * sin((360 - angle) * PI / 180));

	glTexCoord2d(1.0, 1.0);
	glVertex2d(pixelwx + tmp * cos((angle)* PI / 180), pixelwy - tmp * sin((angle)* PI / 180));

	glTexCoord2d(0.0, 1.0);
	glVertex2d(pixelwx + tmp * cos((180 - angle) * PI / 180), pixelwy - tmp * sin((180 - angle) * PI / 180));

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Dart::CheckDartHitMonster(Monster &monster)
{
	if (monster.mstate == 0)
	{
		return;
	}
	int relativeX, relativeY;
	relativeX = abs(monster.x - x);
	relativeY = abs(monster.y - y);
	if (0 <= relativeX && relativeX < 2 && 0 <= relativeY && relativeY < 3)
	{
		if (state == 1)
		{
			monster.hp--;
			dartplayer.Stop(monstergethit);
			dartplayer.PlayOneShot(monstergethit);
			if (monster.hp <= 0)
			{
				dartplayer.Stop(monsterdie);
				dartplayer.PlayOneShot(monsterdie);
				monster.mstate = 0;
			}
			vx *= -1;
			vy *= -1;
			state = 2;
			printf("Fetch it!\n");
		}
		if (state == 4)
		{
			monster.hp -= 3;
			dartplayer.Stop(monstergethit);
			dartplayer.PlayOneShot(monstergethit);
			if (monster.hp <= 0)
			{
				monster.hp -= 3;
				dartplayer.Stop(monsterdie);
				dartplayer.PlayOneShot(monsterdie);
				monster.mstate = 0;
			}
			vx *= -1;
			vy *= -1;
			state = 5;
			printf("Enjoy mode!\n");
		}

	}
}

void Dart::CheckGetByPlayer(Player &player)
{
	if (state == 2 || state == 5)
	{
		int relativeX, relativeY;
		relativeX = abs(player.x - x);
		relativeY = abs(player.y - y);
		if (0 <= relativeX && relativeX < 2 && 0 <= relativeY && relativeY < 2)
		{
			state = 3;
			printf("You Fetched it! ENJOY!\n");
		}
	}
}

void Dart::Fire(Player &player, const char mapvalue[300][300])
{
	int lb, mb, rb, mx, my;
	FsGetMouseEvent(lb, mb, rb, mx, my);
	if (state == 0 && rb == 0)
	{
		return;
	}
	if (state == 0 && rb == 1)
	{
		dartplayer.Stop(dartfire);
		dartplayer.PlayOneShot(dartfire);
		x = (double)player.x;
		y = (double)player.y;
		vx = (mx - 400) / sqrt(pow((mx - 400), 2) + pow((my - 300), 2));
		vy = (my - 300) / sqrt(pow((mx - 400), 2) + pow((my - 300), 2));
		state = 1;
	}
	if (state == 3 && rb == 0)
	{
		return;
	}
	if (state == 3 && rb == 1)
	{
		dartplayer.Stop(dartfire);
		dartplayer.PlayOneShot(dartfire);
		x = (double)player.x;
		y = (double)player.y;
		vx = 2 * (mx - 400) / sqrt(pow((mx - 400), 2) + pow((my - 300), 2));
		vy = 2 * (my - 300) / sqrt(pow((mx - 400), 2) + pow((my - 300), 2));
		state = 4;
	}
	if (state == 1 || state == 2)
	{
		Draw1((x - (player.x - 27)) * 15, (y - (player.y - 20)) * 15);

		if (mapvalue[(int)x][(int)y + 1] == '3' || mapvalue[(int)x][(int)y - 1] == '3')
		{
			state = 0;

		}
		else if (mapvalue[(int)x - 1][(int)y] == '4' || mapvalue[(int)x + 1][(int)y] == '5')
		{
			state = 0;
		}
		else if (mapvalue[(int)x - 2][(int)y - 1] == '4' || mapvalue[(int)x + 1][(int)y - 1] == '4' ||
			mapvalue[(int)x + 1][(int)y + 1] == '4' || mapvalue[(int)x - 1][(int)y + 1] == '4' ||
			mapvalue[(int)x - 1][(int)y - 1] == '5' || mapvalue[(int)x + 1][(int)y - 1] == '5' ||
			mapvalue[(int)x + 1][(int)y + 1] == '5' || mapvalue[(int)x - 1][(int)y + 1] == '5' ||
			mapvalue[(int)x - 1][(int)y - 1] == '3' || mapvalue[(int)x + 1][(int)y - 1] == '3' ||
			mapvalue[(int)x + 1][(int)y + 1] == '3' || mapvalue[(int)x - 1][(int)y + 1] == '3')
		{
			state = 0;
		}
		x += vx;
		y += vy;
	}
	if (state == 4 || state == 5)
	{
		Draw2((x - (player.x - 27)) * 15, (y - (player.y - 20)) * 15);

		if (mapvalue[(int)x][(int)y + 1] == '3' || mapvalue[(int)x][(int)y - 1] == '3')
		{
			state = 0;
		}
		else if (mapvalue[(int)x - 1][(int)y] == '4' || mapvalue[(int)x + 1][(int)y] == '5')
		{
			state = 0;
		}
		else if (mapvalue[(int)x - 2][(int)y - 1] == '4' || mapvalue[(int)x + 1][(int)y - 1] == '4' ||
			mapvalue[(int)x + 1][(int)y + 1] == '4' || mapvalue[(int)x - 1][(int)y + 1] == '4' ||
			mapvalue[(int)x - 1][(int)y - 1] == '5' || mapvalue[(int)x + 1][(int)y - 1] == '5' ||
			mapvalue[(int)x + 1][(int)y + 1] == '5' || mapvalue[(int)x - 1][(int)y + 1] == '5' ||
			mapvalue[(int)x - 1][(int)y - 1] == '3' || mapvalue[(int)x + 1][(int)y - 1] == '3' ||
			mapvalue[(int)x + 1][(int)y + 1] == '3' || mapvalue[(int)x - 1][(int)y + 1] == '3')
		{
			state = 0;
		}
		x += vx;
		y += vy;
	}
}