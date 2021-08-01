
// My render engine, inspired by pico8, tic80, etc
// The idea is to have simple commands for draw tilemap, 
// sprites, etc, similar to those fantasy consoles.

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include "raylib.h"

// Tile map

typedef struct Map {
    uint16_t width;
    uint16_t height;
    uint16_t tileW;
    uint16_t tileH;
    uint16_t imageW;
    uint16_t imageH;
    uint16_t *tiles;
    Texture2D texture;
} Map;

Map* loadMap(const char* fileName, Texture2D texture);
void freeMap(Map *map);
void drawMap(const Map *map, int x, int y);

#endif
