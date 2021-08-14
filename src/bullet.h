#ifndef __BULLET_H__
#define __BULLET_H__

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

void initBullets(void);

void newBullet(int type, float x, float y);

void updateBullets(void);

void drawBullets(void);

void freeBullets(void);

#endif
