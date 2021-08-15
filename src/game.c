#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "game.h"
#include "enemy.h"


static Game game;

int collisionPointRect(float x, float y, Rectangle rec)
{
    return (x >= rec.x) && (x < (rec.x + rec.width)) && (y >= rec.y) && (y < (rec.y + rec.height));
}

int collisionPointCircles(float x, float y, float cx, float cy, float r) {
    float dx = cx - x;
    float dy = cy - y;
    float d = dx * dx + dy * dy;
    return d < r * r;
}

int randomValue(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

void handleInputs(void) {
    game.up = IsKeyDown(KEY_UP);
    game.down = IsKeyDown(KEY_DOWN);
    game.left = IsKeyDown(KEY_LEFT);
    game.right = IsKeyDown(KEY_RIGHT);
    game.shot = IsKeyDown(KEY_X);
    
    if (IsGamepadAvailable(0)) {
        game.up = game.up || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
        game.down = game.down || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        game.left = game.left || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        game.right = game.right || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
        game.shot = game.shot || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }
}

void updateGame(void) {
    handleInputs();
    game.update();
}

void drawGame(void) {
    game.draw();
}

void initGame() {
    game.width = 64;
    game.height = 64;
    game.texture = LoadTexture("tiles.png");
    game.player = getPlayer();
    game.pBullets = getPlayerBulletPool();
    game.enemies = getEnemyPool();
}

Game* getGame(void) {
    return &game;
}




