#include "raylib.h"
#include "engine.h"
#include "game.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int screenWidth = 64;
int screenHeight = 64;
static App* app = 0;

void UpdateDrawFrame(void);     // Update and Draw one frame

void initApp() {
    app = getApp();
    app->width = GetScreenWidth();
    app->height = GetScreenHeight();
}

int main()
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    initApp();
    initGame();
    
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

void UpdateDrawFrame(void)
{
    app->update();
    app->draw();    
}