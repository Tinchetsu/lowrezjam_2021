#include "gameScene.h"
#include "engine.h"
#include "Player.h"
#include <stdio.h>


Game* game;
// static Map* map;
// static Vector2* camera;
// static int tileCollision=-1;

static Player* player;


static void updatePlayer() {
    player->update();
}

static void update() {
    updatePlayer();
}

static Rectangle rectangles[10];
static CharInfo chars[10];

static Font createFont() {
    Image image = LoadImage("resources/minifont.png");

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


static void draw() {
    ClearBackground(GRAY);
    player->draw();
    DrawTextEx(game->font,"01233432545889", (Vector2){0,0}, 5, 1, WHITE);
}

void runGameScene() {
    game = getGame();
    game->update = update;
    game->draw = draw;

    game->font = createFont();
    
    player = getPlayer();
    player->x = 26.f;
    player->y = 50.f;
}
