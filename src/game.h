
#ifndef __GAME_H__
#define __GAME_H__

#include <stdint.h>
#include "raylib.h"
#include "scene.h"
#include "player.h"
#include "player_bullet.h"
#include "enemy.h"

//Game, to make easy draw scenes and stuff
typedef struct Game {
    //screen sizes
    int     width;  
    int     height;

    //game inputs
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;
    uint8_t shot;

    Texture2D texture;
    Font font;

    Player* player;
    PBullet* pBullets;
    Enemy* enemies;
    Scene*  scene;          //current scene
    
    uint32_t score;

    void*   pUserData;      //for storing custom stuff
    
    
    
    void    (*init)(void);
    void    (*run)(void);
} Game;


Game* getGame(void);
int getDeviceScreenWidth(void);
int getDeviceScreenHeight(void);


int collisionPointRect(float x, float y, Rectangle rec);
int collisionPointCircles(float x, float y, float cx, float cy, float r);
int randomValue(int lower, int upper);


#endif
