#include "tilemap.h"
#include <stdio.h>
#include <stdlib.h> 


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(x, lower, upper) (MIN((upper), MAX((x), (lower))))

Map* loadMap(const char* fileName, Texture2D texture) {
    Map *map = (Map*) malloc(sizeof(Map));
    FILE *fp;
    fp = fopen(fileName, "r");
    
    //read map tileW, tileH, imageW, imageH, width, height
    fread(&(map->width),2, 6, fp);
    map->texture = texture;
        
    int tilesSize = map->width * map->height * sizeof(uint16_t);
    map->tiles = (uint16_t*) malloc(tilesSize);
    fread(map->tiles, tilesSize, 1, fp);
    fclose(fp);
    return map;
}

void freeMap(Map *map) {
    if(map->width * map->height > 0) {
        free(map->tiles);
    }
    free(map);
}

void drawMap(const Map *map, int x, int y, int sx, int sy, int w, int h) {
    int tile;
    int _x = x;
    int _y = y;
    sx = CLAMP(sx, 0, map->width);
    sy = CLAMP(sy, 0, map->height);

    int ex = sx + w;
    int ey = sy + h;
    ex = CLAMP(ex, 0, map->width);
    ey = CLAMP(ey, 0, map->height);
    
    for (int j = 0; j < map->height; j++ ) {
        for (int i = sx; i < ex; i++ ) {
            tile = *((uint16_t*) map->tiles + (j*map->width + i)) - 1;
            if(tile>=0) {
                uint16_t offsetx = (tile*map->tileW) % map->imageW;
                uint16_t offsety = (tile / (map->imageH / map->tileH)) * map->tileH;
                DrawTextureRec(map->texture, (Rectangle){offsetx, offsety, map->tileW, map->tileH}, (Vector2){i*8-_x, j*8-_y}, WHITE);
            }
        }
    }
    /*
    char buffer1[255];
    char buffer2[255];
    sprintf(buffer2, "%d,%d\n%d,%d\n%d,%d", sx,sy, ex,ey,map->width,map->height);
    DrawText(buffer1,0,0,0,BLUE);
    DrawText(buffer2,38,0,0,YELLOW);
    */
}

int getMapTile(const Map* map, int x, int y) {
    int tile = -1; //invalid tile
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        tile = (int)map->tiles[x + y * map->width] - 1;
    }
    return tile;
}