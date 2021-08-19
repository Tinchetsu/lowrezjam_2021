#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "raylib.h"
#include <stdint.h>

#define ENEMY_POOL_SIZE 50
#define ENEMY_COL_BOXES 2

enum EnemyType {
	ENEMY1 = 0
};

typedef struct Enemy {
	float x, y;
	int16_t type;
	uint8_t active;
	uint16_t live;
	uint8_t hitTime;
	uint16_t sprite;
	uint16_t tick;
	uint16_t score;
	Rectangle boxes[ENEMY_COL_BOXES];	//up to 2 collsion boxes per enemy
	uint8_t data[64]; //extra data for each enemy, not all of it will be used
	void  (*draw)(struct Enemy*);
	void  (*update)(struct Enemy*);
} Enemy;

Enemy* getEnemyPool(void);
void initEnemies(void);
void updateEnemies(void);
void drawEnemies(void);
void spawnEnemy(int type, float x, float y);

#endif
