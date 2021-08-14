#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <stdint.h>
#include "raylib.h"

enum PlayerState {
    PLAYER_SPAWN=0,
    PLAYER_PLAY,
    PLAYER_DEAD
};

typedef struct Player {
    float x;
    float y;
    float dx;
    float dy;
    int32_t level;
    int32_t lives;
    int32_t tick;
    int8_t alive;
    int8_t state;
    int32_t invulTime;
    Color pixel;
    void  (*draw)(void);
    void  (*update)(void);
} Player;

Player* getPlayer(void);

void spawnPlayer();

#endif
