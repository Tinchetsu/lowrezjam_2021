#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "raylib.h"

typedef struct Player {
    float x;
    float y;
    float gravity;
    void  (*draw)();
} Player;

Player* getPlayer();

#endif
