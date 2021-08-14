#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "raylib.h"
#include <stdint.h>

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
void drawMap(const Map *map, int x, int y, int sx, int sy, int w, int h);
int getMapTile(const Map* map, int x, int y);

#endif
