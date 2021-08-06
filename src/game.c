#include "game.h"
#include "engine.h"

Texture2D texture;
Font font;
Map* map;
static GameData gameData;
static App *app;

float camx=0;
float camy=0;
float speed = 0.5f;


void updateInputs() {
    gameData.up = IsKeyDown(KEY_UP);
    gameData.down = IsKeyDown(KEY_DOWN);
    gameData.left = IsKeyDown(KEY_LEFT);
    gameData.right = IsKeyDown(KEY_RIGHT);
    
    if (IsGamepadAvailable(0)) {
        gameData.up = gameData.up || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
        gameData.down = gameData.down || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        gameData.left = gameData.left || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        gameData.right = gameData.right || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }
}

void updateGame() {

    updateInputs();

    if(gameData.left) {
        camx-=speed;
    }
    if(gameData.right) {
        camx+=speed;
    }
    if(gameData.up) {
        camy-=speed;
    }
    if(gameData.down) {
        camy+=speed;
    }
    
    camera(camx, camy);
}

void drawGame() {
    BeginDrawing();
    ClearBackground(GRAY);
    drawMap(map, 0, 0, 0, 0, map->width, map->height);
    EndDrawing();
}

void initGame() {
    app = getApp();
    app->pUserData = (void*) &gameData;
    app->update = updateGame;
    app->draw = drawGame;
    texture = LoadTexture("resources/tiles.png");
    font = LoadFontEx("resources/tic-computer-6x6-font.ttf", 6, 0, 0);

    Image image = LoadImageFromTexture(font.texture);
    ExportImage(image, "image.png");

    map = loadMap("resources/map", LoadTexture("resources/tiles.png"));
}
