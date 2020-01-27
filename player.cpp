//
//  player.cpp
//  player
//
//  Created by Jincheng Lu on 11/17/19.
//  Copyright © 2019 CMU. All rights reserved.
//

#include "Player.h"

void Player::Initialize(void)//Initialize values
{
    x = 100;
    y = 280;
    heart_x = 20;
    heart_y = 20;
    hp = 5;
}

void Player::CalculatePixelCoord()
{
    x_pixel = 15*(x-1)+7.5;
    y_pixel = 15*(y-1)+7.5;
}

void Player::DrawCharacter(int CharacterNum, int mapx, int mapy)//Draw the player according to players choice
{
    if (CharacterNum == 0)
    {
        png.Decode("character_and_weapon/1.png");
        png.Flip();
        SaveTexture();
		DrawbyMap(mapx, mapy);
    }
    if (CharacterNum == 1)
    {
        png.Decode("character_and_weapon/2.png");
        png.Flip();
        SaveTexture();
        DrawbyMap(mapx, mapy);
    }
    
}

void Player::SaveHeartTexture()
{
    glGenTextures(1, &texId_heart);  // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D, texId_heart);  // Making the texture identifier current (or bring it to the deck)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D
    (GL_TEXTURE_2D,
        0,    // Level of detail
        GL_RGBA,
        png_heart.wid,
        png_heart.hei,
        0,    // Border width, but not supported and needs to be 0.
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        png_heart.rgba);

}

void Player::DrawHeart()
{
    png_heart.Flip();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);  // Begin using texture mapping
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texId_heart);

    glBegin(GL_QUADS);

    double tmp = sqrt(pow(png_heart.hei, 2) + pow(png_heart.wid, 2)) / 2;
    double angle = atan((double)png_heart.hei / (double)png_heart.wid) * 180 / PI;

    glTexCoord2d(0.0, 0.0);
    glVertex2d(heart_x + tmp * cos((180 + angle) * PI / 180), heart_y - tmp * sin((180 + angle) * PI / 180));

    glTexCoord2d(1.0, 0.0);
    glVertex2d(heart_x + tmp * cos((360 - angle) * PI / 180), heart_y - tmp * sin((360 - angle) * PI / 180));

    glTexCoord2d(1.0, 1.0);
    glVertex2d(heart_x + tmp * cos((angle)* PI / 180), heart_y - tmp * sin((angle)* PI / 180));

    glTexCoord2d(0.0, 1.0);
    glVertex2d(heart_x + tmp * cos((180 - angle) * PI / 180), heart_y - tmp * sin((180 - angle) * PI / 180));


    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void Player::DrawHP()//Draw the player HP status on left top, if zero heart means game over
{
    png_heart.Decode("character_and_weapon/heart.png");
    png_heart.Flip();
    SaveHeartTexture();
    if (hp == 0)
    {
        printf("GAME OVER!");
    }
    else
    {
        for (int i = 1; i <= hp; i++)
        {
            DrawHeart();
            heart_x += 20;
        }
        heart_x = 20;
    }
    
}


void Player::PlayerMove(char mapvalue[300][300])//Player Input WSAD to move the character
{
    //auto key = FsInkey();
    if (0 != FsGetKeyState(FSKEY_W))
    {
        if (mapvalue[x][y-1] == '3' || mapvalue[x][y-1] == '4' || mapvalue[x][y-1] == '5')
        {
            
        }
        else
        {
            y -= 1;
        }
    }
    if (0 != FsGetKeyState(FSKEY_S))
    {
        if (mapvalue[x][y+1] == '3' || mapvalue[x][y+1] == '4' || mapvalue[x][y+1] == '5')
        {
            
        }
        else
        {
            y += 1;
        }
    }
    if (0 != FsGetKeyState(FSKEY_A))
    {
        if (mapvalue[x-1][y] == '3' || mapvalue[x-1][y] == '4' || mapvalue[x-1][y] == '5')
        {
            
        }
        else
        {
            x -= 1;
        }
    }
    if (0 != FsGetKeyState(FSKEY_D))
    {
        if (mapvalue[x+1][y] == '3' || mapvalue[x+1][y] == '4' || mapvalue[x+1][y] == '5')
        {
            
        }
        else
        {
            x += 1;
        }
    }
}

void Player::CheckHitByMonster(double monsterhit_x, double monsterhit_y)//Check the player hit by the monster or not
{
    double relativeX, relativeY;
    relativeX = monsterhit_x - x_pixel;
    relativeY = monsterhit_y - y_pixel;
    if (0 <= relativeX && relativeX < 7.5 && 0 <= relativeY && relativeY < 7.5)
    {
        hp --;
    }
    else
    {
        
    }
}








