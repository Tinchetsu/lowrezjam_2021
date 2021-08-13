#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "engine.h"

typedef struct Player {
    float x;
    float y;
    float dx;
    float dy;
    void  (*draw)();
    void  (*update)();
} Player;

Player* getPlayer();

#endif
