#ifndef __PLAYER_H__
#define __PLAYER_H__

typedef struct Player {
    float x;
    float y;
    float dx;
    float dy;
    void  (*draw)(void);
    void  (*update)(void);
} Player;

Player* getPlayer(void);

#endif
