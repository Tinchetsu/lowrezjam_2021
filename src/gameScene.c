#include "gameScene.h"
#include "engine.h"
#include "player.h"
#include "bullet.h"
#include <stdio.h>


Game* game;
// static Map* map;
// static Vector2* camera;
// static int tileCollision=-1;

static Player* player;

static Rectangle rectangles[10];
static CharInfo chars[10];

static Font createFont() {
    Image image = LoadImage("minifont.png");

    rectangles[0] = (Rectangle){0, 0, 3, 5};
    rectangles[1] = (Rectangle){5, 0, 1, 5};
    for(int i=2; i<10; i++) {
        rectangles[i] = (Rectangle){4*i, 0, 3, 5};
    }

    for(int i=0; i<10; i++) {
        chars[i] = (CharInfo){i+48,0,0,0, ImageFromImage(image, rectangles[i])};
    }

    Font font = {5,10,0, LoadTextureFromImage(image), rectangles, chars};
    return font;
}

static void updatePlayer() {
    
    player->update();
}

static void update() {
    updateBullets();
    updatePlayer();
}

static void draw() {
    ClearBackground(BLACK);
    drawBullets();
    player->draw();
    
    DrawTextEx(game->font,"0123456789", (Vector2){0,0}, 5, 1, WHITE);
}

void setGameScene(void) {
    game = getGame();
    game->update = update;
    game->draw = draw;

    game->font = createFont();
    
    initBullets();
    
    player = getPlayer();
    player->x = 26.f;
    player->y = 50.f;
}
