#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "game.h"
#include "gameScene.h"
#include "enemy.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


static Game game;
static RenderTexture2D renderTarget;
static int screenWidth;
static int screenHeight;


int getDeviceScreenWidth(void) {
    #if defined(PLATFORM_WEB)
    int width = 64;
    #elif defined(PLATFORM_ANDROID)
    int width = 640;
    #else
    int width = 640;
    #endif
    return width;
}

int getDeviceScreenHeight(void){
    #if defined(PLATFORM_WEB)
    int height = 64;
    #elif defined(PLATFORM_ANDROID)
    int height = 640;
    #else
    int height = 640;
    #endif
    return height;
}

int collisionPointRect(float x, float y, Rectangle rec)
{
    return (x >= rec.x) && (x < (rec.x + rec.width)) && (y >= rec.y) && (y < (rec.y + rec.height));
}

int collisionPointCircles(float x, float y, float cx, float cy, float r) {
    float dx = cx - x;
    float dy = cy - y;
    float d = dx * dx + dy * dy;
    return d < r * r;
}

int randomValue(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

void handleInputs(void) {
    game.up = IsKeyDown(KEY_UP);
    game.down = IsKeyDown(KEY_DOWN);
    game.left = IsKeyDown(KEY_LEFT);
    game.right = IsKeyDown(KEY_RIGHT);
    game.shot = IsKeyDown(KEY_X);
    
    if (IsGamepadAvailable(0)) {
        game.up = game.up || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
        game.down = game.down || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        game.left = game.left || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        game.right = game.right || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
        game.shot = game.shot || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }
}

static void update(void) {
    handleInputs();
    game.scene->update();
}

static void draw(void) {
    game.scene->draw();
}


static void UpdateDrawFrame() {
    update();
#ifdef PLATFORM_WEB
    BeginDrawing();
    ClearBackground(GRAY);
    draw();
    EndDrawing();
#else
    
    BeginTextureMode(renderTarget);
    draw();
    EndTextureMode();

    
    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawRectangle(0,0,(float)renderTarget.texture.width, (float)renderTarget.texture.height,BLUE);
    DrawRectangle(0,0,screenWidth,screenWidth,RED);
    
    DrawTexturePro(renderTarget.texture,
        (Rectangle) {0, 0, (float)renderTarget.texture.width, (float)-renderTarget.texture.height},
        (Rectangle) {0, 0, screenWidth, screenHeight},
        (Vector2) {0, 0},
        0.0f,
        WHITE
    );
    
    EndDrawing();
    
    
#endif

}

static void init(void) {
    
    screenWidth = getDeviceScreenWidth();
    screenHeight = getDeviceScreenHeight();
    
    game.width = 64;
    game.height = 64;
    game.texture = LoadTexture("tiles.png");
    game.player = getPlayer();
    game.pBullets = getPlayerBulletPool();
    game.enemies = getEnemyPool();
    
    setGameScene();
}

static void run() {
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
        SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
        renderTarget = LoadRenderTexture(game.width, game.height);
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            UpdateDrawFrame();
        }
    #endif
}


Game* getGame(void) {
    game.init = init;
    game.run = run;
    return &game;
}




