#include <stdio.h>
#include <stdlib.h> 
#include "engine.h"

static App app = {0};

App* getApp() {
    return &app;
}

Map* loadMap(const char* fileName, Texture2D texture) {
    Map *map = (Map*) malloc(sizeof(Map));
    FILE *fp;
    fp = fopen(fileName, "r");
    
    //read map tileW, tileH, imageW, imageH, width, height
    fread(&(map->width),2, 6, fp);
    printf("map.width: %d\n", map->width);
    printf("map.height: %d\n", map->height);
    printf("map.tileW: %d\n", map->tileW);
    printf("map.tileH: %d\n", map->tileH);
    printf("map.imageW: %d\n", map->imageW);
    printf("map.imageH: %d\n", map->imageH);

    map->texture = texture;
        
    int tilesSize = map->width * map->height * sizeof(uint16_t);
    printf("size: %d\n", tilesSize);
    map->tiles = (uint16_t*) malloc(tilesSize);
    fread(map->tiles, tilesSize, 1, fp);
    fclose(fp);
    return map;
}

void freeMap(Map *map) {
    if(map->width * map->height > 0) {
        free(map->tiles);
    }
}

void drawMap(const Map *map, int x, int y) {
    int tile;
    for (int j = 0; j < map->height; j++ ) {
        for (int i = 0; i < map->width; i++ ) {
            tile = *((uint16_t*) map->tiles + (j*map->width + i)) - 1;
            if(tile>=0) {
                uint16_t offsetx = (tile*map->tileW) % map->imageW;
                uint16_t offsety = (tile / (map->imageH / map->tileH)) * map->tileH;
                DrawTextureRec(map->texture, (Rectangle){offsetx, offsety, map->tileW, map->tileH}, (Vector2){i*8 + x, j*8 + y}, WHITE);
            }
        }
    }
}
