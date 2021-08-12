
#include "Player.h"

static Player player;


static void draw() {
    //DrawRectangle(player.x, player.y, 8, 8, RED);
    DrawTextureRec(getGame()->texture, (Rectangle){8, 24, 8, 8}, (Vector2){player.x, player.y}, WHITE);
}

Player* getPlayer() {
    player.draw = draw;
    player.gravity = 0.5f;
    return &player;
}
