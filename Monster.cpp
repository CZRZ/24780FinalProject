#include "Monster.h"
//#include <algorithm>
#include <math.h>

Monster::Monster()
{	
	png.Decode("character_and_weapon/monster.png");
	png.Flip();
	SaveTexture();
	weapon.Decode("character_and_weapon/monsterweapon.png");
	weapon.Flip();
	SaveWeaponTexture();
	hp = 5;
	mstate = 1;
	wstate = 0;
	start = std::chrono::system_clock::now();
	x = 100 + rand() % 50;//need to change
	y = 100 + rand() % 50;
	vx = 1;
	vy = 1;
	weaponx = x;
	weapony = y;
	wvx = 1;
	wvy = 1;
}

void Monster::DrawMonster(int playerx, int playery)
{
	if (mstate == 0)
	{
		return;
	}
	double pixelx = (x - (playerx - 27)) * 15;
	double pixely = (y - (playery - 20)) * 15;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texId);

	glBegin(GL_QUADS);

	double tmp = sqrt(pow(png.hei, 2) + pow(png.wid, 2));
	double angle = atan((double)png.hei / (double)png.wid) * 180 / PI;

	glTexCoord2d(0.0, 0.0);
	glVertex2d(pixelx + tmp * cos((180 + angle) * PI / 180), pixely - tmp * sin((180 + angle) * PI / 180));

	glTexCoord2d(1.0, 0.0);
	glVertex2d(pixelx + tmp * cos((360 - angle) * PI / 180), pixely - tmp * sin((360 - angle) * PI / 180));

	glTexCoord2d(1.0, 1.0);
	glVertex2d(pixelx + tmp * cos((angle)* PI / 180), pixely - tmp * sin((angle)* PI / 180));

	glTexCoord2d(0.0, 1.0);
	glVertex2d(pixelx + tmp * cos((180 - angle) * PI / 180), pixely - tmp * sin((180 - angle) * PI / 180));

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Monster::SaveWeaponTexture()
{
	glGenTextures(1, &wtexId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, wtexId);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		weapon.wid,
		weapon.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		weapon.rgba);
}

void Monster::DrawWeapon(int pixelwx, int pixelwy)
{

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, wtexId);

	glBegin(GL_QUADS);

	double tmp = sqrt(pow(weapon.hei, 2) + pow(weapon.wid, 2)) / 4;
	double angle = atan((double)weapon.hei / (double)weapon.wid) * 180 / PI;

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

double Monster::timecount(std::chrono::system_clock::time_point starttime)
{
	auto nowtime = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(nowtime - starttime);
	double DurInSec;
	DurInSec = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
	return DurInSec;
}

bool Monster::CheckHit(int playerx, int playery)
{	
	int relativex = abs(weaponx - playerx);
	int relativey = abs(weapony - playery);
	if (0 <= relativex && relativex < 2 && 0 <= relativey && relativey < 2 && wstate == 1)
	{
		wstate = 0;
		return true;
	}
	else
	{
		return false;
	}
}

int Monster::Hp(bool hit)
{
	double end = timecount(start);
	if (hit == 1)
	{
		hp--;
		return hp;
	}
	else if (end >= 3)//3 seconds
	{
		hp++;
		return hp;
	}
	else
	{
		return hp;
	}
}

void Monster::Move(const char mapvalue[300][300])
{
	if (mstate == 0)
	{
		return;
	}
	double end = timecount(start);
	if (end > 0.5 && mstate != 0)
	{	
		start = std::chrono::system_clock::now();
		if (mapvalue[x][y + 3] == '3' || mapvalue[x][y - 1] == '3')
		{
			vy = -vy;

		}
		else if (mapvalue[x - 2][y] == '4' || mapvalue[x + 2][y] == '5')
		{
			vx = -vx;
		}
		else if (mapvalue[x - 2][y - 1] == '4' || mapvalue[x + 2][y - 1] == '4' ||
			mapvalue[x + 2][y + 3] == '4' || mapvalue[x - 2][y + 3] == '4' ||
			mapvalue[x - 2][y - 1] == '5' || mapvalue[x + 2][y - 1] == '5' ||
			mapvalue[x + 2][y + 3] == '5' || mapvalue[x - 2][y + 3] == '5' ||
			mapvalue[x - 2][y - 1] == '3' || mapvalue[x + 2][y - 1] == '3' ||
			mapvalue[x + 2][y + 3] == '3' || mapvalue[x - 2][y + 3] == '3')
		{
			vx = -vx;
			vy = -vy;

		}
		x += vx;
		y += vy;
	}
}

void Monster::timetodie(double time)
{
	if (time > 5)
	{
		mstate = 0;
	}
}

void Monster::Attack(int playerx, int playery, const char mapvalue[300][300])
{
	double relativex;
	double relativey;
	if (mstate == 0)
	{
		return;
	}
	if (wstate == 0) {
		relativex = (double)playerx - x;
		relativey = (double)playery - y;
		wvx = relativex / sqrt(pow(relativex, 2) + pow(relativey, 2));
		wvy = relativey / sqrt(pow(relativex, 2) + pow(relativey, 2));
		if (-20 <= relativex && relativex <= 20 && -25 <= relativey && relativey <= 25)
		{
			weaponx = x;
			weapony = y;
			wstate = 1;
		}
	}
	if (wstate == 1)
	{	
		DrawWeapon((weaponx - (playerx - 27)) * 15, (weapony -(playery - 20)) * 15);	
		if (mapvalue[(int)weaponx][(int)weapony + 1] == '3' || mapvalue[(int)weaponx][(int)weapony - 1] == '3')
		{
			wstate = 0;

		}
		else if (mapvalue[(int)weaponx - 1][(int)weapony] == '4' || mapvalue[(int)weaponx + 1][(int)weapony] == '5')
		{
			wstate = 0;
		}
		else if (mapvalue[(int)weaponx - 2][(int)weapony - 1] == '4' || mapvalue[(int)weaponx + 1][(int)weapony - 1] == '4' ||
			mapvalue[(int)weaponx + 1][(int)weapony + 1] == '4' || mapvalue[(int)weaponx - 1][(int)weapony + 1] == '4' ||
			mapvalue[(int)weaponx - 1][(int)weapony - 1] == '5' || mapvalue[(int)weaponx + 1][(int)weapony - 1] == '5' ||
			mapvalue[(int)weaponx + 1][(int)weapony + 1] == '5' || mapvalue[(int)weaponx - 1][(int)weapony + 1] == '5' ||
			mapvalue[(int)weaponx - 1][(int)weapony - 1] == '3' || mapvalue[(int)weaponx + 1][(int)weapony - 1] == '3' ||
			mapvalue[(int)weaponx + 1][(int)weapony + 1] == '3' || mapvalue[(int)weaponx - 1][(int)weapony + 1] == '3')
		{
			wstate = 0;
		}
		weaponx += wvx;
		weapony += wvy;
	}
}