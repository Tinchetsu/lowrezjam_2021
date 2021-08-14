#include "enemy.h"
#include "game.h"
#include "enemy_bullet.h"
#include <memory.h>
#include <stdio.h>

static Enemy enemyPool[ENEMY_POOL_SIZE];
static Rectangle sprites[] = { {240,240,7,7}, {248,240,7,7}, {232,248,3,3} };
static Game* game;
#define HIT_TIME 3

//---------------------------------------------------------------------------------------------
void updateEnemy1(Enemy* enemy) {

    if (enemy->hitTime > 0) {
        enemy->hitTime--;
    }

    Rectangle bbox = (Rectangle){ 
        (int)(enemy->x + enemy->boxes[0].x), 
        (int)(enemy->y + enemy->boxes[0].y), 
        enemy->boxes[0].width, 
        enemy->boxes[0].height 
    };

    // check collision with player
    if (game->player->invulTime==0 &&
        collisionPointRect((int)game->player->x, (int)game->player->y, bbox)) {
        enemy->hitTime = HIT_TIME;
        enemy->live--;
        spawnPlayer();
    }

    // check collision with player bullets
    if (enemy->y >= 0) {
        for (int i = 0; i < PBULLETS_POOL_SIZE; i++) {
            PBullet* bullet = game->pBullets + i;
            if (bullet->active) {
                if (collisionPointRect((int)bullet->x, (int)bullet->y, bbox)) {
                    bullet->active = 0;
                    enemy->live--;
                    enemy->hitTime = HIT_TIME;
                    game->score += enemy->score;
                }
            }
        }
    }

    if (enemy->y >= 70) {
        enemy->active = 0;
    }

    if (enemy->live <= 0) {
        game->score += 500;
        enemy->active = 0;
    }

    if (enemy->y >= 0 && enemy->tick % 50 == 0) {
        spawnEnemyBullet(ENEMY_BULLET2, enemy->x+3, enemy->y+3, 1);
    }

    enemy->y += 0.25;
    
    enemy->tick++;
}

void drawEnemy1(Enemy* enemy) {
    int sprite = enemy->sprite + enemy->hitTime > 0 ? 1 : 0;
    DrawTextureRec(game->texture, sprites[sprite], (Vector2) { (int)enemy->x, (int)enemy->y }, WHITE);
    Color color = enemy->tick == 0 ? RED : BLUE;
    color.a = 128;
}

void spawnEnemy1(Enemy* enemy, float x, float y) {
    enemy->x = x;
    enemy->y = y;
    enemy->live = 10;
    enemy->active = 1;
    enemy->sprite = 0;
    enemy->update = updateEnemy1;
    enemy->draw = drawEnemy1;
    enemy->score = 5;
    enemy->boxes[0] = (Rectangle) {1, 1, 5, 5};
}
//---------------------------------------------------------------------------------------------

void updateEnemies() {
    for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
        if (enemyPool[i].active) {
            enemyPool[i].update(enemyPool + i);
        }
    }
}

void drawEnemies() {
    for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
        if (enemyPool[i].active) {
            enemyPool[i].draw(enemyPool + i);
        }
    }
}

Enemy* getFreeEnemy() {
    Enemy* enemy = 0;
    for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
        if (!enemyPool[i].active) {
            enemy = enemyPool + i;
            break;
        }
    }
    return enemy;
}


Enemy* getEnemyPool() {
    return enemyPool;
}

void initEnemies() {
    game = getGame();
    memset(enemyPool, 0, sizeof(Enemy) * ENEMY_POOL_SIZE);
}

void spawnEnemy(int type, float x, float y) {
    Enemy *enemy = getFreeEnemy();
    if (enemy) {
        spawnEnemy1(enemy, x, y);
    }
}


