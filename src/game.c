#include "game.h"
#include "engine.h"

Texture2D texture;
Font font;
Map* map;
extern App *app;

float camx=0;
float camy=0;
float speed = 0.5f;

void updateGame() {
    if(IsKeyDown(KEY_LEFT)) {
        camx-=speed;
    }
    if(IsKeyDown(KEY_RIGHT)) {
        camx+=speed;
    }
    if(IsKeyDown(KEY_UP)) {
        camy-=speed;
    }
    if(IsKeyDown(KEY_DOWN)) {
        camy+=speed;
    }
    
    camera((int)camx, camy);
}

void drawGame() {
    BeginDrawing();
    ClearBackground(GRAY);
    drawMap(map, 0, 0);
    DrawTextEx(font, "abcdefghi ", (Vector2){ 0.f, 0.f }, 6.f, 0.f, WHITE);    
    EndDrawing();   
}

void initGame() {
    app = getApp();
    app->update = updateGame;
    app->draw = drawGame;
    texture = LoadTexture("resources/tiles.png");
    font = LoadFontEx("resources/tic-computer-6x6-font.ttf", 6, 0, 0);

    Image image = LoadImageFromTexture(font.texture);
    ExportImage(image, "image.png");

    map = loadMap("resources/map", LoadTexture("resources/tiles.png"));
}
