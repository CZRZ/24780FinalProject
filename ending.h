#ifndef ENDING_H_INCLUDED
#define ENDING_H_INCLUDED


#include "yssimplesound.h"

#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"

#include "ysglfontdata.h"

class Ending
{
public:
	double x, y, drawy;
	int r, g, b;
	char memberName[256];

	YsRawPngDecoder png;
	YsSoundPlayer endingplayer;
	YsSoundPlayer::SoundData endingsound;
	Ending();
	void DrawList();
	void DrawBackground();
	void Move();
	void Legend();
	void Display();
};
#endif // !ENDING_H_INCLUDED
