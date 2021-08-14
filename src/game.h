
// My render engine, inspired by pico8, tic80, etc
// The idea is to have simple commands for draw tilemap, 
// sprites, etc, similar to those fantasy consoles.

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include "raylib.h"

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

    void*   pUserData;      //for storing custom stuff
    void    (*update)(void);
    void    (*draw)(void);
} Game;

Game* getGame(void);
void updateGame(void);
void drawGame(void);


#endif
