#ifndef __GAME_H__
#define __GAME_H__

#include <stdint.h>

typedef struct Game {
    int     width;
    int     height;
    int     cameraX;
    int     cameraY;

    //game inputs
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;

    void*   pUserData;      //for storing custom stuff
    void    (*update)();
    void    (*draw)();
} Game;

Game* initGame();

#endif
