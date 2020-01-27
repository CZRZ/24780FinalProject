#include "open.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include "npc.h"
#include "Menu.h"
#include "yssimplesound.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "yspng.h"
#include "door.h"
#include "Weapon.h"
#include "ending.h"

class soundtrack
{
public:
	YsSoundPlayer player;
	YsSoundPlayer::SoundData playergethit;
	soundtrack();
};

soundtrack::soundtrack()
{
	player.MakeCurrent();
	player.Start();
	if (YSOK != playergethit.LoadWav("SoundTrack/monstergethit.wav"))
	{
		printf("Error!  Cannot load monstergethit.wav!\n");
	}
}



int main(void)
{
	srand(time(NULL));
	//FsOpenWindow(0, 0, 800, 601, 1);
	run();
	Restart:
	int ballnum = 5;
	Ball ball[10];
	Dart dart;
	soundtrack st;
	Doorlist doors;
	Menu menu;
	menu.DisplayInOne();
	NPClist npcs;
	Player P1;
	Ending end;
	//auto start = std::chrono::system_clock::now();
	P1.Initialize();
	//***************************************************************************************
	const int monsterNum = 15;

	Monster RegularM[monsterNum];
	for (int i = 0; i < 5; i++)
	{
		RegularM[i].x = 150 + rand() % 20;//need to change
		RegularM[i].y = 250 + rand() % 20;
	}
	for (int i = 5; i < 10; i++)
	{
		RegularM[i].x = 100 + rand() % 50;//need to change
		RegularM[i].y = 100 + rand() % 50;
	}
	for (int i = 10; i < 15; i++)
	{
		RegularM[i].x = 264 + rand() % 10;//need to change
		RegularM[i].y = 95 + rand() % 10;
	}
	Monster Quiz;
	Quiz.hp = 20;
	Quiz.x = 130;
	Quiz.y = 220;
	Monster Midterm;
	Midterm.hp = 30;
	Midterm.x = 145;
	Midterm.y = 135;
	Monster Final;
	Final.hp = 50;
	Final.x = 270;
	Final.y = 128;

	Quiz.png.Decode("character_and_weapon/quiz.png");
	Quiz.png.Flip();
	Quiz.SaveTexture();
	Quiz.weapon.Decode("character_and_weapon/quizweapon.png");
	Quiz.weapon.Flip();
	Quiz.SaveWeaponTexture();

	Midterm.png.Decode("character_and_weapon/midterm.png");
	Midterm.png.Flip();
	Midterm.SaveTexture();
	Midterm.weapon.Decode("character_and_weapon/midtermweapon.png");
	Midterm.weapon.Flip();
	Midterm.SaveWeaponTexture();

	Final.png.Decode("character_and_weapon/final.png");
	Final.png.Flip();
	Final.SaveTexture();
	Final.weapon.Decode("character_and_weapon/finalweapon.png");
	Final.weapon.Flip();
	Final.SaveWeaponTexture();

	//***************************************************************************************

	Map map;
	supportItem items[monsterNum];
	supportItem luckbags;
	luckbags.LucybagStart();
	supportItem itemquiz;
	supportItem itemmidterm;
	supportItem itemfinal;
	itemquiz.itemType = 4;
	itemmidterm.itemType = 4;
	itemfinal.itemType = 4;

	int lb, mb, rb, mx, my;

	int counter = 0;

	P1.hp = 5;
	while (true)
	{
		if (P1.x == 83 && P1.y == 277)
		{
			P1.x = 175;
			P1.y = 45;
		}
		if (P1.x == 155 && P1.y == 59)
		{
			P1.x = 84;
			P1.y = 278;
		}
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}

		if (P1.hp <= 0)
		{
			st.player.End();
			map.mapplayer.End();
			menu.gameover();
			goto Restart;
		}

		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Draw Map, Player and Monster
		doors.NormalControl(P1.x, P1.y, map.mapvalueforread, map.mapValue);
		doors.SpecialDoors[0].SpecialControl(Quiz, map.mapvalueforread, map.mapValue);
		doors.SpecialDoors[1].SpecialControl(Midterm, map.mapvalueforread, map.mapValue);
		doors.SpecialDoors[2].SpecialControl(Final, map.mapvalueforread, map.mapValue);

		map.drawMap(P1);
		doors.DoorsDraw(P1.x, P1.y);
		P1.PlayerMove(map.mapvalueforread);
		P1.DrawCharacter(menu.PlayerNum, 400, 300);
		P1.DrawHP();
		P1.CalculatePixelCoord();
		npcs.drawlist(P1.x, P1.y);
		FsGetMouseEvent(lb, mb, rb, mx, my);
		if (lb == 1)
		{
			for (int i = 0; i < ballnum; i++)
			{
				if (counter == 0)
				{
					counter += 1;
					break;
				}
				if (ball[i].state == 0 )
				{
					ball[i].CheckFire(P1, map.mapvalueforread, mx, my);
					break;
				}
			}
		}

		for (int i = 0; i < ballnum; i++)
		{
			ball[i].Fire(P1, map.mapvalueforread);

		}

		dart.Fire(P1, map.mapvalueforread);
		//*****************************************
		Quiz.DrawMonster(P1.x, P1.y);
		Quiz.Attack(P1.x, P1.y, map.mapvalueforread);
		if (Quiz.CheckHit(P1.x, P1.y))
		{
			P1.hp--;
			ballnum--;
			if (ballnum <= 5)
			{
				ballnum = 5;
			}
		}
		Quiz.Move(map.mapvalueforread);
		dart.CheckDartHitMonster(Quiz);
		dart.CheckGetByPlayer(P1);

		Midterm.DrawMonster(P1.x, P1.y);
		Midterm.Attack(P1.x, P1.y, map.mapvalueforread);
		if (Midterm.CheckHit(P1.x, P1.y))
		{
			P1.hp--;
			ballnum--;
			if (ballnum <= 5)
			{
				ballnum = 5;
			}
		}
		Midterm.Move(map.mapvalueforread);
		dart.CheckDartHitMonster(Midterm);
		dart.CheckGetByPlayer(P1);

		Final.DrawMonster(P1.x, P1.y);
		Final.Attack(P1.x, P1.y, map.mapvalueforread);
		if (Final.CheckHit(P1.x, P1.y))
		{
			P1.hp--;
		}
		Final.Move(map.mapvalueforread);
		dart.CheckDartHitMonster(Final);
		dart.CheckGetByPlayer(P1);

		for (int j = 0; j < ballnum; j++)
		{
			ball[j].CheckHitMonster(Quiz, ballnum);
			ball[j].CheckHitMonster(Midterm, ballnum);
			ball[j].CheckHitMonster(Final, ballnum);
		}

		itemquiz.Initialize(Quiz, 1);
		itemquiz.getLocation(Quiz.x, Quiz.y);
		itemquiz.checkView(P1, itemquiz.itemType);
		itemquiz.Comsume(P1, RegularM[0], ballnum, ball);
		luckbags.Lucybag(P1);
		itemmidterm.Initialize(Midterm, 1);
		itemmidterm.getLocation(Midterm.x, Midterm.y);
		itemmidterm.checkView(P1, itemmidterm.itemType);
		itemmidterm.Comsume(P1, RegularM[0], ballnum, ball);

		itemfinal.Initialize(Final, 1);
		itemfinal.getLocation(Final.x, Final.y);
		itemfinal.checkView(P1, itemfinal.itemType);
		itemfinal.Comsume(P1, RegularM[0], ballnum, ball);
		
		for (int i = 0; i < monsterNum; i++)
		{
			RegularM[i].DrawMonster(P1.x, P1.y);
			dart.CheckDartHitMonster(RegularM[i]);
			dart.CheckGetByPlayer(P1);
			for (int j = 0; j < ballnum; j++)
			{
				ball[j].CheckHitMonster(RegularM[i], ballnum);
			}
			if (RegularM[i].CheckHit(P1.x, P1.y))
			{
				P1.hp--;
				st.player.Stop(st.playergethit);
				st.player.PlayOneShot(st.playergethit);
			}

			RegularM[i].Move(map.mapvalueforread);
			RegularM[i].Attack(P1.x, P1.y, map.mapvalueforread);

			//*********************************************************
			items[i].Initialize(RegularM[i], monsterNum);
			items[i].getLocation(RegularM[i].x, RegularM[i].y);
			items[i].Initialize(RegularM[i], monsterNum);

			items[i].checkView(P1, items[i].itemType);
			items[i].Comsume(P1, RegularM[0], ballnum, ball);
		}

		if (doors.NormalDoors[4].state == 1)
		{
			map.mapplayer.End();
			end.Display();
		}
		if (P1.x == 90 && P1.y == 270)
		{
			P1.x = 170;
			P1.y = 50;
		}

		FsSwapBuffers();
		FsSleep(25);
	}
	return 0;

}

