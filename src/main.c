#include "raylib.h"
#include "game.h"

int main() {
    InitWindow(getDeviceScreenWidth(), getDeviceScreenHeight(), "raylib [core] example - basic window");
    Game *game = getGame();
    game->init();
    
    game->run();    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
