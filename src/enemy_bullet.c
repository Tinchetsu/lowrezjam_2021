#include "enemy_bullet.h"
#include "game.h"
#include <memory.h>

static Game* game;
static EBullet bullets[EBULLETS_POOL_SIZE];

static Rectangle sprites[] = { 
    {228,248,3,3}, {232,248,3,3}, 
    {232,248,3,3} 
};

static void update1(EBullet* bullet) {
    bullet->x += bullet->dx;
    bullet->y += bullet->dy;

    if (bullet->x < -4 || bullet->x > 68 || bullet->y < -4 || bullet->y > 68)
        bullet->active = 0;

    //check player collision
    if (collisionPointCircles((int)game->player->x, (int)game->player->y, (int)bullet->x, (int)bullet->y, (int)bullet->radius)) {
        bullet->active = 0;
    }

    if (bullet->tick % 5 == 0) {
        bullet->sprite = bullet->sprite == 0 ? 1 : 0;
    }

    bullet->tick++;
}

static void draw1(EBullet* bullet) {
    DrawTextureRec(game->texture, sprites[bullet->sprite], (Vector2) { (int)bullet->x-1, (int)bullet->y-1 }, WHITE);
}

static void spawnEBullet1(EBullet* bullet, float x, float y, float speed) {
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

void spawnEnemyBullet(int type, float x, float y, float speed) {
    EBullet* bullet = getFreeBullet();
    if (bullet) {
        switch (type)
        {
        case ENEMY_BULLET1:
            spawnEBullet1(bullet, x, y, speed);
            break;

        default:
            break;
        }
    }
}


