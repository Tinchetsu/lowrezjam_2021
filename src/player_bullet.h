#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

enum BulletType {
    PLAYER_BULLET1=0,
    ENEMY_BULLET
};


typedef struct Bullet {
    float x;
    float y;
    float dx;
    float dy;
    int type;
    int active;
    void  (*update)(struct Bullet*);
    void  (*draw)(struct Bullet*);
} Bullet;

void initPlayerBullets(void);
void newPlayerBullet(int type, float x, float y);
void updatePlayerBullets(void);
void drawPlayerBullets(void);
void freePlayerBullets(void);

#endif
