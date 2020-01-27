//
//  Header.h
//  24780_Items
//
//  Created by Kangchun Wang on 11/17/19.
//  Copyright © 2019 Kangchun Wang. All rights reserved.
//

#ifndef Item_h
#define Item_h
#include "yssimplesound.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"

class supportItem
{
public:
    int state[10], itemType, dropNum, rangeR, bagState[3];
    int GameViewWei, GameViewHei;
    int x[10], y[10];
	bool stateTrans = true;
    YsRawPngDecoder png;
	YsSoundPlayer::SoundData eatitem;
	YsSoundPlayer itemplayer;
    
	supportItem();
    
    void Initialize(Monster &monster, int monsterNum);
    void getLocation(int monster_x, int monster_y);
	void checkView(Player &player, int monsterType);
    
//    void DrawSingleTest(int monsterType, double x, double y);
	
    void DrawSingle(int monsterType, int x, int y, int state);
    void DrawTotal(int monsterType);
    int CheckConsume(Player &player, int ix, int iy);
    void Comsume(Player &player, Monster &monster, int &ballnum, Ball ball[]);
    
    void LucybagStart();
    void Lucybag(Player &player);
};

#endif 
