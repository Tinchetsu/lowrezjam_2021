
// My render engine, inspired by pico8, tic80, etc
// The idea is to have simple commands for draw tilemap, 
// sprites, etc, similar to those fantasy consoles.

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include "raylib.h"

// The game app. Here I hook update and draw functions
// Also contains common data

typedef struct App {
    int     width;
    int     height;
    int     cameraX;
    int     cameraY;
    void*   pUserData;      //for storing custom stuff
    void    (*update)();
    void    (*draw)();
} App;

App* getApp();

void camera(int x, int y);

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
