#include "Menu.h"

double Menu::timecount(std::chrono::system_clock::time_point starttime)
{
	auto nowtime = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(nowtime - starttime);
	double DurInSec;
	DurInSec = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
	return DurInSec;
}

void Menu::Draw(double x, double y)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texId);

	glBegin(GL_QUADS);

	double tmp = sqrt(pow(png.hei, 2) + pow(png.wid, 2)) / 2;
	double angle = atan((double)png.hei / (double)png.wid) * 180 / PI;

	glTexCoord2d(0.0, 0.0);
	glVertex2d(x + tmp * cos((180 + angle) * PI / 180), y - tmp * sin((180 + angle) * PI / 180));

	glTexCoord2d(1.0, 0.0);
	glVertex2d(x + tmp * cos((360 - angle) * PI / 180), y - tmp * sin((360 - angle) * PI / 180));

	glTexCoord2d(1.0, 1.0);
	glVertex2d(x + tmp * cos((angle)* PI / 180), y - tmp * sin((angle)* PI / 180));

	glTexCoord2d(0.0, 1.0);
	glVertex2d(x + tmp * cos((180 - angle) * PI / 180), y - tmp * sin((180 - angle) * PI / 180));


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void Menu::BackGround()
{

	Draw(400,300);
	glRasterPos2i(155, 100);
	//glColor3ub(0, 0, 0);
	YsGlDrawFontBitmap20x28("Secret Dungeon in CMU");
}

void Menu::DisplayInOne()
{
	while (true)
	{
		FsPollDevice();
		menuplayer.PlayBackground(maininterface);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (FSKEY_ESC == FsInkey())
		{
			menuplayer.End();
			break;
		}
		BackGround();
		
		MenuDisplayFrame();
		CheckMouseState();
		FsSwapBuffers();
		if (StartGame == 1)
		{
			menuplayer.End();
			break;
		}
		FsSleep(25);
	}
}

Menu::Menu()
{	
	// set all the state
	png.Decode("opening_and_ending/menubg.png");

	menuplayer.MakeCurrent();
	menuplayer.Start();
	if (YSOK != maininterface.LoadWav("SoundTrack/maininterface.wav"))
	{
		printf("Error!  Cannot load maininterface.wav!\n");
	}
	if (YSOK != interfaceclick.LoadWav("SoundTrack/interfaceclick.wav"))
	{
		printf("Error!  Cannot load interfaceclick.wav!\n");
	}
	if (YSOK != gameoversound.LoadWav("SoundTrack/gameoversound.wav"))
	{
		printf("Error!  Cannot load gameoversound.wav!\n");
	}
	png.Flip();
	SaveTexture();
	PlayerNum = 0;
	MaleState = 0;
	FemaleState = 0;
	Display = 1;
	CharOptionBlockState = 1;
	LoadBlockState = 0;
	ExitBlockState = 1;
	BackBlockState = 1;
	PlayBlockState = 0;
	CharBlockState = 0;
	StartGame = 0;
}

void Menu::MenuDisplayFrame()
{
	switch (Display)
	{
	case 1://No Click
		//Display character button, load game button, exit button
		//glColor3ub(1, 1, 1);
		glRasterPos2i(247, 230);
		YsGlDrawFontBitmap16x20("Select Character");
		//glRasterPos2i(303, 330);
		//YsGlDrawFontBitmap16x20("Load Game");
		glRasterPos2i(343, 430);
		YsGlDrawFontBitmap16x20("Exit");
		break;	
	case 2://Click Character Button
		//Display male, female and back button
		//glColor3ub(1, 1, 1);
		
		glRasterPos2i(343, 230);
		YsGlDrawFontBitmap16x20("Male");//0
		glRasterPos2i(327, 330);
		YsGlDrawFontBitmap16x20("Female");//1
		glRasterPos2i(343, 430);
		YsGlDrawFontBitmap16x20("Back");
		break;		
	case 3://Click Male or Female
		//Display Play and Back Button
		//glColor3ub(1, 1, 1);
		
		glRasterPos2i(343, 330);
		YsGlDrawFontBitmap16x20("Play");
		glRasterPos2i(343, 430);
		YsGlDrawFontBitmap16x20("Back");
		break;
	case 4://Click load game button
		//glColor3ub(1, 1, 1);
	
		glRasterPos2i(295, 230);
		YsGlDrawFontBitmap16x20("Load Files");
		glRasterPos2i(343, 330);
		YsGlDrawFontBitmap16x20("Play");
		glRasterPos2i(343, 430);
		YsGlDrawFontBitmap16x20("Back");
		break;
		//Display load files, Back Button and Play Button
	case 5://Click exit button
		
		exit(0);
		break;
		//exit
	case 6://Click Play Button
		
		StartGame = 1;
		break;
		//Menu disapears and initialize map and character and monster
	}
}

void Menu::CheckMouseState()
{	
	start = std::chrono::system_clock::now();
	int lb, mb, rb, mx, my;
	FsGetMouseState(lb, mb, rb, mx, my);
	if ((mx>=244 && mx <= 503 && my <= 230 && my >= 210)
		&& lb == 1 && CharOptionBlockState == 1)// Main Menu
	{
		Display = 2;
		CharOptionBlockState = 0;
		LoadBlockState = 0;
		ExitBlockState = 0;
		BackBlockState = 1;
		PlayBlockState = 0;
		MaleState = 1;
		FemaleState = 1;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
	}

	if ((mx >= 343 && mx <= 407 && my <= 230 && my >= 210) 
		&& lb == 1 && MaleState == 1)// Character Menu Male Choose
	{
		Display = 3;
		CharOptionBlockState = 0;
		LoadBlockState = 0;
		ExitBlockState = 0;
		BackBlockState = 1;
		PlayBlockState = 1;
		MaleState = 0;
		FemaleState = 0;
		PlayerNum = 0;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
	}

	if ((mx >= 327 && mx <= 423 && my <= 330 && my >= 310)
		&& lb == 1 && FemaleState == 1)// Character Menu Female Choose
	{
		Display = 3;
		CharOptionBlockState = 0;
		LoadBlockState = 0;
		ExitBlockState = 0;
		BackBlockState = 1;
		PlayBlockState = 1;
		MaleState = 0;
		FemaleState = 0;
		PlayerNum = 1;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
	}

	if ((mx >= 311 && mx <= 447 && my <= 330 && my >= 310) 
		&& lb == 1 && LoadBlockState == 1)// Load Game Menu
	{
		Display = 4;
		CharOptionBlockState = 0;
		LoadBlockState = 0;
		ExitBlockState = 0;
		BackBlockState = 1;
		PlayBlockState = 1;
		CharBlockState = 0;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
	}

	if ((mx >= 343 && mx <= 407 && my <= 430 && my >= 410) 
		&& lb == 1 && ExitBlockState == 1)// Exit
	{
		Display = 5;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
	}

	if ((mx >= 343 && mx <= 407 && my <= 430 && my >= 410)
		&& lb == 1 && BackBlockState == 1)// Back to Main Menu
	{
		Display = 1;
		CharOptionBlockState = 1;
		LoadBlockState = 0;
		ExitBlockState = 1;
		BackBlockState = 1;
		PlayBlockState = 0;
		CharBlockState = 0;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
	}

	if ((mx >= 343 && mx <= 407 && my <= 330 && my >= 310)
		&& lb == 1 && PlayBlockState == 1) // Play
	{
		Display = 6;
		double end = timecount(start);
		while (end <= 0.3) {
			end = timecount(start);
		}
		menuplayer.Stop(interfaceclick);
		menuplayer.PlayOneShot(interfaceclick);
		return;
		return;
	}
}


void Menu::gameover()
{
	YsRawPngDecoder gameover;
	menuplayer.Start();
	gameover.Decode("gameover.png");
	gameover.Flip();
	menuplayer.Stop(gameoversound);
	menuplayer.PlayOneShot(gameoversound);
	FsPollDevice();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRasterPos2i(0, gameover.hei);
//	printf("%d %d", gameover.wid, gameover.hei);
	glDrawPixels(gameover.wid, gameover.hei, GL_RGBA, GL_UNSIGNED_BYTE, gameover.rgba);
	FsSwapBuffers();
	FsSleep(5000);
}