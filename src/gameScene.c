#include "gameScene.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "player_bullet.h"
#include "enemy_bullet.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Star {
    float x;
    float y;
    int z;
} Star;

#define TOTAL_STARS 50
static Star stars[TOTAL_STARS];

enum State {
    GAME_PLAYING = 0,
    GAME_OVER
};



static Game* game;
// static Map* map;
// static Vector2* camera;
// static int tileCollision=-1;

static Player* player;

#define TOTAL_CHARS 26

static Rectangle rectangles[TOTAL_CHARS];
static CharInfo chars[TOTAL_CHARS];

static Font createFont() {
    Image image = LoadImage("minifont.png");

    for(int i=0; i<TOTAL_CHARS; i++) {
        rectangles[i] = (Rectangle){4*i, 0, 3, 5};
    }
    //rectangles[1] = (Rectangle){5, 0, 1, 5};
    rectangles[0] = (Rectangle){0, 0, 1, 5};   // space
    rectangles[1] = (Rectangle){5, 0, 1, 5};   // !
    rectangles[7] = (Rectangle){29, 0, 1, 5};  // '
    rectangles[8] = (Rectangle){32, 0, 2, 5};  // (
    rectangles[9] = (Rectangle){37, 0, 2, 5};  // )
    rectangles[12] = (Rectangle){48, 0, 2, 5}; // ,
    rectangles[14] = (Rectangle){57, 0, 1, 5}; // .
    rectangles[17] = (Rectangle){69, 0, 1, 5}; // 1
    
    for(int i=0; i<TOTAL_CHARS; i++) {
        chars[i] = (CharInfo){i+32,0,0,0, ImageFromImage(image, rectangles[i])};
    }

    Font font = {5,TOTAL_CHARS,0, LoadTextureFromImage(image), rectangles, chars};
    return font;
}

static void initBackground(void) {
    for (int i = 0; i < TOTAL_STARS; i++) {
        stars[i].x = randomValue(0, 63);
        stars[i].y = randomValue(0, 63);
        stars[i].z = randomValue(2, 6);
    }
}

static void updateBackground(void) {
    for (int i = 0; i < TOTAL_STARS; i++) {
        stars[i].y += stars[i].z * 0.1;
        if (stars[i].y > 64) {
            stars[i].x = randomValue(0, 63);
            stars[i].y = 0;
        }
    }
}

static void drawBackground(void) {
    for (int i = 0; i < TOTAL_STARS; i++) {
        int c = ((float)stars[i].z) / 4 * 255;
        if (stars[i].z == 2) c = 100;
        if (stars[i].z == 3) c = 140;
        if (stars[i].z == 4) c = 180;
        if (stars[i].z == 5) c = 210;
        if (stars[i].z == 6) c = 250;

        Color color = (Color){ c,c,c,c };
        DrawPixel(stars[i].x, stars[i].y, color);
    }
}
static int tick = 0;
static void update() {
    if (tick % 100 == 0) {
        spawnEnemy(ENEMY1, randomValue(4, 60), -1 * randomValue(10, 90));
    }
    updateBackground();
    updateEnemies();
    updateEnemyBullets();
    updatePlayerBullets();
    player->update();
    tick++;
}

static void draw() {
    ClearBackground(BLACK);
    drawBackground();
    drawPlayerBullets();
    player->draw();
    drawEnemies();
    drawEnemyBullets();

    char text[128];
    sprintf(text, "%d", game->score);
    DrawTextEx(game->font, text, (Vector2) { 2, 2 }, 5, 1, GRAY);
    DrawTextEx(game->font, text, (Vector2) { 1, 1 }, 5, 1, WHITE);
    
}

void setGameScene(void) {
    game = getGame();
    game->update = update;
    game->draw = draw;

    game->font = createFont();
    
    initBackground();
    initPlayerBullets();
    initEnemies();
    initEnemyBullets();
    
    player = getPlayer();
    player->x = 26.f;
    player->y = 50.f;

    //for (int i = 0; i < 10; i++) {
        //spawnEnemy(ENEMY1, random(4, 60), -1 * random(10, 90));
    //}

    spawnPlayer();
}
