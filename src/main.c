#include "raylib.h"
#include "engine.h"
#include "gameScene.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#ifdef PLATFORM_WEB
int screenWidth = 64;
int screenHeight = 64;
#else
int screenWidth = 640;
int screenHeight = 640;
RenderTexture2D target;
#endif

static Game* game = 0;

void initGame(void) {
    game = getGame();
    game->width = 64;
    game->height = 64;
    game->texture = LoadTexture("tiles.png");
    game->font = LoadFontEx("tic-computer-6x6-font.ttf", 6, 0, 0);
    setGameScene();
}

void UpdateDrawFrame(void) {
    updateGame();

#ifdef PLATFORM_WEB
    BeginDrawing();
    ClearBackground(GRAY);    
    drawGame();
    EndDrawing();
#else
    BeginTextureMode(target);
    drawGame();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(target.texture,
        (Rectangle) {0, 0, (float)target.texture.width, (float)-target.texture.height},
        (Rectangle) {0, 0, screenWidth, screenHeight},
        (Vector2) {0, 0},
        0.0f,
        WHITE
    );
    EndDrawing();
#endif

}

int main() {
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    initGame();
    
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    target = LoadRenderTexture(game->width, game->height);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
