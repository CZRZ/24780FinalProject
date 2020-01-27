#include "Character.h"

void Character::SaveTexture()
{
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,
		png.wid,
		png.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png.rgba);
}

void Character::DrawbyMap(int mapx, int mapy)
{
	png.Flip();
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
	glVertex2d(mapx + tmp * cos((180 + angle) * PI / 180), mapy - tmp * sin((180 + angle) * PI / 180));

	glTexCoord2d(1.0, 0.0);
	glVertex2d(mapx + tmp * cos((360 - angle) * PI / 180), mapy - tmp * sin((360 - angle) * PI / 180));

	glTexCoord2d(1.0, 1.0);
	glVertex2d(mapx + tmp * cos((angle)* PI / 180), mapy - tmp * sin((angle)* PI / 180));

	glTexCoord2d(0.0, 1.0);
	glVertex2d(mapx + tmp * cos((180 - angle) * PI / 180), mapy - tmp * sin((180 - angle) * PI / 180));


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}