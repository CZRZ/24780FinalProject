#ifndef player_h
#define player_h
#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "Character.h"

class Player: public Character
{
public:
    int heart_x;
    int heart_y;
    double x_pixel;
    double y_pixel;
    
    GLuint texId_heart;
    YsRawPngDecoder png_heart;
    
    void Initialize(void);
    void CalculatePixelCoord(void);
    void DrawCharacter(int CharacterNum, int mapx, int mapy);
    void SaveHeartTexture(void);
    void DrawHeart(void);
    void DrawHP(void);
    void PlayerMove(char mapvalue[300][300]);
	void CheckHitByMonster(double monsterhit_x, double monsterhit_y);
};


#endif /* player_h */
