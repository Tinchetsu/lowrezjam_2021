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
    if (player.state == PLAYER_SPAWN) {
        player.y -= 0.25;
        if (player.y <= 50) {
            player.state = PLAYER_PLAY;
        }
    }
    if (player.state == PLAYER_PLAY) {
        move();
        shot();
    }
    if (player.invulTime > 0) {
        player.invulTime--;
    }
    player.tick++;
}

static void draw() {
    static int colorIndex = 0;

    if (player.invulTime > 0) {
        if(player.invulTime%2==0)
            DrawTextureRec(getGame()->texture, sprites[sprite], (Vector2) { (int)player.x - 3, (int)player.y - 4 }, WHITE);
    }
    else {
        DrawTextureRec(getGame()->texture, sprites[sprite], (Vector2) { (int)player.x - 3, (int)player.y - 4 }, WHITE);
    }
    if (player.tick % 5 == 0) {
        colorIndex = !colorIndex;
        player.pixel = colorIndex ? RED : YELLOW;
    }
    DrawPixel((int)player.x, (int)player.y, player.pixel);
}

Player* getPlayer(void) {
    game = getGame();
    player.alive = 1;
    player.lives = 1;
    player.level = 0;
    player.update = update;
    player.draw = draw;
    player.pixel = RED;
    return &player;
}


void spawnPlayer() {
    player.x = 32;
    player.y = 70;
    player.invulTime = 200;
    player.state = PLAYER_SPAWN;
}
