#include "player.h"
#include "game.h"
#include "player_bullet.h"
#include <stdio.h>

static Player player = {};
static Game *game;
static float speed = 0.5f;
static Rectangle sprites[3] = {{0,0,8,8},{8,0,8,8},{8,0,-7,8}};
static int sprite = 0;

int shotDelay = 0;

static void move() {
    player.dx = 0;
    player.dy = 0;
    sprite = 0;
    if(game->left && !game->right) { 
        player.dx=-speed;
        sprite = 1;
    }
    if(game->right && !game->left) {
        player.dx=speed;
        sprite = 2;
    }
    if(game->up && !game->down) {
        player.dy=-speed;
    }
    if(game->down && !game->up) {
        player.dy=speed;
    }
    player.x += player.dx;
    player.y += player.dy;
}

static void shot() {
    
    if(game->shot) {
        if(shotDelay==0) {
            shotDelay = 5;
            newPlayerBullet(PLAYER_BULLET1, player.x+3, player.y);
        }
    }
    
    shotDelay--;
    if(shotDelay < 0)
        shotDelay = 0;
}

static void update() {
    move();
    shot();
}

static void draw() {
    //DrawRectangle(player.x, player.y, 8, 8, RED);
    DrawTextureRec(getGame()->texture, sprites[sprite], (Vector2){(int)player.x, (int)player.y}, WHITE);
}

Player* getPlayer(void) {
    game = getGame();
    player.update = update;
    player.draw = draw;
    return &player;
}
