#include "game.h"
#include "engine.h"
#include "Player.h"
#include <stdio.h>

static Game game;
static Font font;
static Map* map;
static Vector2* camera;
static int tileCollision=-1;

void doStuff() {
    
}

static Player* player;

float speed = 0.5f;


void handleInputs() {
    game.up = IsKeyDown(KEY_UP);
    game.down = IsKeyDown(KEY_DOWN);
    game.left = IsKeyDown(KEY_LEFT);
    game.right = IsKeyDown(KEY_RIGHT);
    
    if (IsGamepadAvailable(0)) {
        game.up = game.up || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
        game.down = game.down || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        game.left = game.left || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        game.right = game.right || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }
}


void updatePlayerPosition() {
    int checkTileX = (player->x + 4) / 8;
    int checkTileY = (player->y + 7) / 8;

    tileCollision = getMapTile(map, checkTileX, checkTileY);
    if(tileCollision>=0) {
        if((player->y + 8) > checkTileY * 8) {
            player->y = (checkTileY * 8) - 8;
        }
    }

    tileCollision = getMapTile(map, (player->x + 4) / 8, (player->y + 7) / 8);
}

void updatePlayer() {
    if(game.left) { player->x-=speed; }
    if(game.right) { player->x+=speed; }
    if(game.up) { player->y-=speed; }
    if(game.down) { player->y+=speed; }

    //gravity
    //player->y += player->gravity;

    //tile collisions
    tileCollision = getMapTile(map, (player->x + 4) / 8, (player->y + 7) / 8);

    updatePlayerPosition();
}

void updateGame() {
    handleInputs();
    updatePlayer();
}

void drawGame() {
    ClearBackground(BLACK);
    drawMap(map, 0, 0, 0, 0, map->width, map->height);
    player->draw();

    char buffer[255];
    sprintf(buffer, "%d", tileCollision);
    DrawText(buffer,0,0,0,BLUE);
}

Game* initGame() {
    game.width = 64;
    game.height = 64;
    game.update = updateGame;
    game.draw = drawGame;
    camera = getCamera();
    font = LoadFontEx("resources/tic-computer-6x6-font.ttf", 6, 0, 0);
    map = loadMap("resources/map", LoadTexture("resources/tiles.png"));

    player = getPlayer();
    player->x = 8.f;
    player->y = 0.f;

    return &game;
}
