#include "bullet.h"
#include "engine.h"
#include "player.h"
#include <stdlib.h>
#include <memory.h>


#define MAX_BULLETS 3

static Bullet* bullets = 0;

static Game* game;
static Player* player;

static float speed=2;

static void update1(Bullet* bullet) {
    bullet->x+= bullet->dx;
    bullet->y+= bullet->dy;
    if(bullet->y < - 2)
        bullet->active = 0;
}

static void draw1(Bullet* bullet) {
    //DrawRectangle(bullet->x, bullet->y, 2, 2, RED);
    DrawCircle(bullet->x+1, bullet->y+1, 2, BLUE);
    DrawTextureRec(game->texture, (Rectangle){16,0,1,6}, (Vector2){bullet->x, bullet->y}, WHITE);
    
}

void initBullets(void) {
    game = getGame();
    bullets = (Bullet*) malloc (MAX_BULLETS * sizeof(Bullet));
    memset(bullets, 0, sizeof(Bullet) * MAX_BULLETS);
}

Bullet* getFreeBullet(){
    Bullet* bullet= 0;
    for(int i=0; i < MAX_BULLETS; i++) {
        if(!bullets[i].active) {
            bullet = bullets + i;
        }
    }
    return bullet;
}

void newBullet(int type, float x, float y){
    Bullet* bullet = getFreeBullet();
    if(bullet) {
        bullet->x = x;
        bullet->y = y;
        bullet->dx = 0;
        bullet->dy = -speed;
        bullet->active = 1;
        bullet->update = update1;
        bullet->draw = draw1;
    }
}

void updateBullets(void) {
    for(int i=0; i < MAX_BULLETS; i++) {
        if(bullets[i].active) {
            bullets[i].update(bullets + i);
        }
    }
}

void drawBullets(void) {
    for(int i=0; i < MAX_BULLETS; i++) {
        if(bullets[i].active) {
            bullets[i].draw(bullets + i);
        }
    }
}


void freeBullets(void) {
    
}
