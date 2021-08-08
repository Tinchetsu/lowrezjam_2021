#include "raylib.h"
#include "engine.h"
#include "game.h"

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

void UpdateDrawFrame(void) {
    game->update();

#ifdef PLATFORM_WEB
    BeginDrawing();
    ClearBackground(GRAY);    
    game->draw();
    EndDrawing();
#else
    BeginTextureMode(target);
    game->draw();
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
    game = initGame();
    
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
