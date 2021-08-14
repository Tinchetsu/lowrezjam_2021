#include "gameScene.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "player_bullet.h"
#include "enemy_bullet.h"
#include <stdio.h>

typedef struct Star {
    float x;
    float y;
} Star;


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

static void updateBackground(void) {
}

static void update() {
    updateEnemies();
    updateEnemyBullets();
    updatePlayerBullets();
    player->update();
}

static void draw() {
    ClearBackground(BLACK);
    drawPlayerBullets();
    player->draw();
    drawEnemies();
    drawEnemyBullets();

    EBullet *eb = getEnemyBulletPool();
    int used = 0;
    for (int i = 0; i < EBULLETS_POOL_SIZE; i++) {
        if (eb[i].active) {
            used++;
        }
    }
    //char buffer[128];
    //sprintf(buffer, "used %d", used);
    //DrawText(buffer, 0, 0, 8, WHITE);
}

void setGameScene(void) {
    game = getGame();
    game->update = update;
    game->draw = draw;

    game->font = createFont();
    
    initPlayerBullets();
    initEnemies();
    initEnemyBullets();
    
    player = getPlayer();
    player->x = 26.f;
    player->y = 50.f;


    spawnEnemy(ENEMY1, 32, 10);
}
