
#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>
#include "raylib.h"

typedef struct Map {
    
    uint16_t layers;
    uint16_t tileW;
    uint16_t tileH;
    uint16_t imageW;
    uint16_t imageH;
    uint16_t width;
    uint16_t height;
    uint16_t *tiles;
    Texture2D texture;
} Map;

Map loadMap(const char* fileName);

void freeMap(Map map);

void drawMap(Map map, int x, int y, uint16_t layer);

#endif