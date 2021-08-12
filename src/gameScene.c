#include "gameScene.h"
#include "engine.h"
#include "Player.h"
#include <stdio.h>


Game* game;
// static Map* map;
// static Vector2* camera;
// static int tileCollision=-1;

static Player* player;

float speed = 0.5f;

static void updatePlayer() {
    if(game->left) { player->x-=speed; }
    if(game->right) { player->x+=speed; }
    if(game->up) { player->y-=speed; }
    if(game->down) { player->y+=speed; }
}

static void update() {
    updatePlayer();
}

static void draw() {
    ClearBackground(BLACK);
    //drawMap(map, 0, 0, 0, 0, map->width, map->height);
    player->draw();

    // char buffer[255];
    // sprintf(buffer, "%d", tileCollision);
    // DrawText(buffer,0,0,0,BLUE);
}

void runGameScene() {
    game = getGame();
    game->update = update;
    game->draw = draw;
    
    player = getPlayer();
    player->x = 26.f;
    player->y = 50.f;
}
