#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__
#include <stdint.h>
#include "raylib.h"

#define PBULLETS_POOL_SIZE 50

enum PlayerBulletType {
    PLAYER_BULLET1 = 0,
    PLAYER_BULLET2,

};

typedef struct PBullet {
    float x;
    float y;
    float dx;
    float dy;
    uint16_t type;
    uint16_t sprite;
    uint8_t active;
    void  (*update)(struct PBullet*);
    void  (*draw)(struct PBullet*);
} PBullet;

PBullet* getPlayerBulletPool();
void initPlayerBullets(void);
void updatePlayerBullets(void);
void drawPlayerBullets(void);
void spawnPlayerBullet(int type, float x, float y);
Rectangle* pBulletSprites();

#endif
