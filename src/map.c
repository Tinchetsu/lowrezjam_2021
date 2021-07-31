#include <stdio.h>
#include <stdlib.h> 
#include "map.h"

Map loadMap(const char* fileName) {
    Map map; 
    FILE *fp;
    fp = fopen(fileName, "r");
    fread(&map.layers, 2, 1, fp);
    
    if(map.layers <= 0) {
        fclose(fp);
        return map;
    }
    
    //read map tileW, tileH, imageW, imageH, width, height
    fread(&map.tileW,2, 6, fp);
    printf("map.tileW: %d\n", map.tileW);
    printf("map.tileH: %d\n", map.tileH);
    printf("map.imageW: %d\n", map.imageW);
    printf("map.imageH: %d\n", map.imageH);
    printf("map.width: %d\n", map.width);
    printf("map.height: %d\n", map.height);

    map.texture = LoadTexture("resources/tiles.png");
        
    int tilesSize = map.layers * map.width * map.height * sizeof(uint16_t);
    printf("size: %d\n", tilesSize);
    map.tiles = (uint16_t*) malloc(tilesSize);
    fread(map.tiles, tilesSize, 1, fp);
    fclose(fp);
    return map;
}

void freeMap(Map map) {
    if(map.layers * map.width * map.height > 0) {
        free(map.tiles);
    }
}

void drawMap(Map map, int x, int y, uint16_t layer) {
    int tile;
    for (int j = 0; j < map.height; j++ ) {
        for (int i = 0; i < map.width; i++ ) {
            tile = *((uint16_t*) map.tiles + (j*map.width + i)) - 1;
            if(tile>=0) {
                uint16_t offsetx = (tile*map.tileW) % map.imageW;
                uint16_t offsety = (tile / (map.imageH / map.tileH)) * map.tileH;
                DrawTextureRec(map.texture, (Rectangle){offsetx, offsety, map.tileW, map.tileH}, (Vector2){i*8 + x, j*8 + y}, WHITE);
            }
        }
    }

    //DrawTexture(map.texture, x, y, WHITE);
}

