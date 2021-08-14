#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "game.h"


static Game game;

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
}


Game* getGame(void) {
    return &game;
}
