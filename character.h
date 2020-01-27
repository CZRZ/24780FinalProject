#ifndef Character_h
#define Character_h
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include <time.h>
#include <math.h>

const double PI = 3.1415926;
class Character
{
public:
    int x, y;
    int vx, vy;
    int hp; //health point
	GLuint texId=1;
	YsRawPngDecoder png;
	void SaveTexture();
	void DrawbyMap(int mapx, int mapy);
};

#endif /* Character_h */
