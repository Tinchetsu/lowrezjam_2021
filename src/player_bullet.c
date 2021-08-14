#include "player_bullet.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

static Game* game;
static Enemy* enemyPool;
static PBullet bullets[PBULLETS_POOL_SIZE];

static Rectangle sprites[] = { {238,248,1,4}, {236,248,1,5}, {232,248,3,3} };



static void update1(PBullet* bullet) {
    bullet->x+= bullet->dx;
    bullet->y+= bullet->dy;

    if(bullet->y < - 2)
        bullet->active = 0;
}

static void draw1(PBullet* bullet) {
    //DrawCircle(bullet->x+1, bullet->y+1, 2, BLUE);
    DrawTextureRec(game->texture, sprites[bullet->sprite], (Vector2){(int)bullet->x, (int)bullet->y-1}, WHITE);
}

void spawnPBullet1(PBullet* bullet, float x, float y) {
    game = getGame();
    bullet->x = x;
    bullet->y = y;
    bullet->dx = 0;
    bullet->dy = -2;
    bullet->sprite = 1;
    bullet->active = 1;
    bullet->update = update1;
    bullet->draw = draw1;
}



void updatePlayerBullets(void) {
    for (int i = 0; i < PBULLETS_POOL_SIZE; i++) {
        if (bullets[i].active) {
            bullets[i].update(bullets + i);
        }
    }
}

void drawPlayerBullets(void) {
    for (int i = 0; i < PBULLETS_POOL_SIZE; i++) {
        if (bullets[i].active) {
            bullets[i].draw(bullets + i);
        }
    }
}

PBullet* getPlayerBulletPool() {
    return bullets;
}

void initPlayerBullets(void) {
    game = getGame();
    enemyPool = getEnemyPool();
    memset(bullets, 0, sizeof(PBullet) * PBULLETS_POOL_SIZE);
}

static PBullet* getFreeBullet(){
    PBullet* bullet= 0;
    for(int i=0; i < PBULLETS_POOL_SIZE; i++) {
        if(!bullets[i].active) {
            bullet = bullets + i;
            break;
        }
    }
    return bullet;
}

void spawnPlayerBullet(int type, float x, float y){
    PBullet* bullet = getFreeBullet();
    if(bullet) {
        switch (type)
        {
        case PLAYER_BULLET1:
            spawnPBullet1(bullet, x, y);
            break;

        default:
            break;
        }
    }
}
