
#include "Player.h"

static Player player = {};
static Game *game;
static float speed = 0.5f;
static Rectangle sprites[3] = {{8,24,8,8},{16,24,8,8},{16,24,-7,8}};
static int sprite = 0;

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


static void update() {
    move();
}

static void draw() {
    //DrawRectangle(player.x, player.y, 8, 8, RED);
    DrawTextureRec(getGame()->texture, sprites[sprite], (Vector2){player.x, player.y}, WHITE);
}

Player* getPlayer() {
    game = getGame();
    player.update = update;
    player.draw = draw;
    return &player;
}
