#include "Player.h"

static Player player;

static void draw() {
    DrawRectangle(player.x, player.y, 8, 8, RED);
}

Player* getPlayer() {
    player.draw = draw;
    player.gravity = 0.5f;
    return &player;
}
