/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//#define PLATFORM_WEB

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

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //tic-80-wide-font.ttf
    
    texture = LoadTexture("resources/tiles.png");
    font = LoadFontEx("resources/tic-computer-6x6-font.ttf", 6, 0, 0);

    Image image = LoadImageFromTexture(font.texture);
    ExportImage(image, "image.png");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
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
        //DrawTexture(texture, 0, 0, WHITE);
        //DrawText("64x64 asdf", 1, 1, 10, GRAY);
        //DrawTextEx(font, "abcdefghi\njklmnoprst\nuvwxyz\n1234567890", fontPosition,6, 0.0f, WHITE);
        DrawTextEx(font, "abcdefghi ", (Vector2){ 0.f, 0.f }, 6.f, 0.f, WHITE);
        DrawTextEx(font, "jklmnoprs ", (Vector2){ 0.f, 7.f }, 6.f, 0.f, WHITE);
        DrawTextEx(font, "tuvwxyz   ", (Vector2){ 0.f, 14.f}, 6.f, 0.f, WHITE);
        DrawTextEx(font, "1234567890", (Vector2){ 0.f, 21.f}, 6.f, 0.f, WHITE);
        
    EndDrawing();
    //----------------------------------------------------------------------------------
}