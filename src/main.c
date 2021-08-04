#include "raylib.h"
#include "engine.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 64;
int screenHeight = 64;
Texture2D texture;
Font font;
Map* map;

void UpdateDrawFrame(void);     // Update and Draw one frame

void initApp() {
    App* app = getApp();
    app->width = GetScreenWidth();
    app->height = GetScreenHeight();
}

int main()
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    initApp();
    
    texture = LoadTexture("resources/tiles.png");
    font = LoadFontEx("resources/tic-computer-6x6-font.ttf", 6, 0, 0);

    Image image = LoadImageFromTexture(font.texture);
    ExportImage(image, "image.png");

    map = loadMap("resources/map", LoadTexture("resources/tiles.png"));

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
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
        ClearBackground(GRAY);
        drawMap(map, 0, 0);
        DrawTextEx(font, "abcdefghi ", (Vector2){ 0.f, 0.f }, 6.f, 0.f, WHITE);
        
    EndDrawing();
}