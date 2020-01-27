#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "yssimplesound.h"

#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"

#include <time.h>
#include "Character.h"
#include <chrono>
#include "ysglfontdata.h"

class Menu : public Character
{
public:
	YsSoundPlayer::SoundData maininterface;
	YsSoundPlayer::SoundData interfaceclick;
	YsSoundPlayer::SoundData gameoversound;
	YsSoundPlayer menuplayer;
	int PlayerNum;
	int MaleState;
	int FemaleState;
	int Display;
	int StartGame;
	int CharOptionBlockState;
	int LoadBlockState;
	int ExitBlockState;
	int BackBlockState;
	int PlayBlockState;
	int CharBlockState;
	std::chrono::system_clock::time_point start;

	Menu();
	void DisplayInOne();
	void MenuDisplayFrame();
	void CheckMouseState();
	void BackGround();
	void Draw(double x, double y);
	double timecount(std::chrono::system_clock::time_point starttime);
	void gameover();
}; 
#endif // !MENU_H_INCLUDED