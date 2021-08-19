#include "enemy_bullet.h"
#include "game.h"
#include "player.h"
#include <memory.h>
#include "raymath.h"

static Game* game;
static EBullet bullets[EBULLETS_POOL_SIZE];

static Rectangle sprites[] = { 
    {228,248,3,3}, {232,248,3,3}, 
    {232,248,3,3} 
};

static EBullet* getFreeBullet() {
    EBullet* bullet = 0;
    for (int i = 0; i < EBULLETS_POOL_SIZE; i++) {
        if (!bullets[i].active) {
            bullet = bullets + i;
            break;
        }
    }
    return bullet;
}

//************************************************************************************************************
static void update1(EBullet* bullet) {
    bullet->x += bullet->dx;
    bullet->y += bullet->dy;

    if (bullet->x < -4 || bullet->x > 68 || bullet->y < -4 || bullet->y > 68)
        bullet->active = 0;

    //check player collision
    if (game->player->invulTime == 0
        && collisionPointCircles((int)game->player->x, (int)game->player->y, (int)bullet->x, (int)bullet->y, (int)bullet->radius))
    {
        bullet->active = 0;
        spawnPlayer();
    }

    if (bullet->tick % 5 == 0) {
        bullet->sprite = bullet->sprite == 0 ? 1 : 0;
    }

    bullet->tick++;
}

static void draw1(EBullet* bullet) {
    DrawTextureRec(game->texture, sprites[bullet->sprite], (Vector2) { (int)bullet->x-1, (int)bullet->y-1 }, WHITE);
}

static void spawnEBullet1(float x, float y, float speed) {
    EBullet* bullet = getFreeBullet();
    if (bullet) {
        game = getGame();
        bullet->x = x;
        bullet->y = y;
        bullet->dx = 0;
        bullet->dy = speed;
        bullet->active = 1;
        bullet->update = update1;
        bullet->radius = 2;
        bullet->draw = draw1;
    }
    
}

//************************************************************************************************************

static void spawnEBullet2_1(float x, float y, float angle) {
    EBullet* bullet = getFreeBullet();
    if (bullet) {
        game = getGame();
        bullet->x = x;
        bullet->y = y;

        bullet->dx = cos(angle)*0.5f;
        bullet->dy = sin(angle) * 0.5f;
        bullet->active = 1;
        bullet->update = update1;
        bullet->radius = 2;
        bullet->draw = draw1;
    }
}

static void spawnEBullet2(float x, float y, float speed) {
    
    Vector2 v1 = (Vector2){ game->player->x, game->player->y };
    Vector2 v2 = (Vector2){ x, y };
    float angle = atan2f(v1.y - v2.y, v1.x - v2.x);
    
    spawnEBullet2_1(x, y, angle - PI*.1);
    spawnEBullet2_1(x, y, angle);
    spawnEBullet2_1(x, y, angle + PI * .1);
}





void updateEnemyBullets(void) {
    for (int i = 0; i < EBULLETS_POOL_SIZE; i++) {
        if (bullets[i].active) {
            bullets[i].update(bullets + i);
        }
    }
}

void drawEnemyBullets(void) {
    for (int i = 0; i < EBULLETS_POOL_SIZE; i++) {
        if (bullets[i].active) {
            bullets[i].draw(bullets + i);
        }
    }
}

EBullet* getEnemyBulletPool() {
    return bullets;
}

void initEnemyBullets(void) {
    game = getGame();
    memset(bullets, 0, sizeof(EBullet) * EBULLETS_POOL_SIZE);
}

void spawnEnemyBullet(int type, float x, float y, float speed) {    
    switch (type)
    {
        case ENEMY_BULLET1:
            spawnEBullet1(x, y, speed);
            break;
        case ENEMY_BULLET2:
            spawnEBullet2(x, y, speed);
            break;

        default:
            break;
    }
    
}


