#ifndef __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "raylib.h"
#include <stdint.h>

//Probably a horrible idea, but the gamejam time is over soon!
#define EBULLETS_POOL_SIZE 500

enum EnemyBulletType {
    ENEMY_BULLET1 = 0,
    ENEMY_BULLET2,
    ENEMY_BULLET3,
    ENEMY_BULLET4,
    ENEMY_BULLET5,
    ENEMY_BULLET6,
    ENEMY_BULLET7,
    ENEMY_BULLET8,
    ENEMY_BULLET9,
    ENEMY_BULLET10,
    ENEMY_BULLET11,
    ENEMY_BULLET12,
    ENEMY_BULLET13,
    ENEMY_BULLET14

};

typedef struct EBullet {
    float x;
    float y;
    float dx;
    float dy;
    float radius;
    uint16_t type;
    uint16_t sprite;
    uint16_t tick;
    uint8_t active;
    void  (*update)(struct EBullet*);
    void  (*draw)(struct EBullet*);
} EBullet;


EBullet* getEnemyBulletPool();
void initEnemyBullets(void);
void updateEnemyBullets(void);
void drawEnemyBullets(void);
void spawnEnemyBullet(int type, float x, float y, float speed);

Rectangle* eBulletSprites();


#endif
