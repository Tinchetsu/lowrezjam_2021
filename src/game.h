#ifndef __GAME_H__
#define __GAME_H__

#include <stdint.h>

typedef struct GameData {
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;
} GameData;

void initGame();

#endif
