
// My render engine, inspired by pico8, tic80, etc
// The idea is to have simple commands for draw tilemap, 
// sprites, etc, similar to those fantasy consoles.

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include "raylib.h"

Vector2 *getCamera();

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

    Texture2D texture;
    Font font;

    void*   pUserData;      //for storing custom stuff
    void    (*update)();
    void    (*draw)();
} Game;

Game* getGame();
void updateGame();
void drawGame();


#endif
