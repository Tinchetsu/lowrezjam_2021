#include "player.h"
#include "game.h"
#include "player_bullet.h"
#include <stdio.h>

static Player player;
static Game *game;
static float speed = 0.5f;
static Rectangle sprites[3] = {{240,248,8,8},{248,248,8,8},{248,248,-7,8}};
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
            spawnPlayerBullet(PLAYER_BULLET1, player.x, player.y-2);
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
    DrawTextureRec(getGame()->texture, sprites[sprite], (Vector2){(int)player.x-3, (int)player.y-4}, WHITE);
    DrawPixel((int)player.x + 8, (int)player.y - 8, WHITE);
    //DrawRectangle(player.x, player.y, 8, 8, (Color) { 255, 255, 255, 128 });
}

Player* getPlayer(void) {
    game = getGame();
    player.level = 0;
    player.update = update;
    player.draw = draw;
    return &player;
}
