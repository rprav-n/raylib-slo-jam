#include <iostream>
#include "raylib.h"

using namespace std;

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;
const float SCALE = 4.f;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Edge Of Void");

    Texture2D bg = LoadTexture("./assets/graphics/environment/bg.png");
    const int bgMoveSpeed = 200;
    float bgY = {};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        bgY += bgMoveSpeed * dt;
        if (bgY >= bg.height * SCALE)
        {
            bgY = 0.f;
        }

        Vector2 bgOnePos = {0.f, bgY};
        DrawTextureEx(bg, bgOnePos, 0.f, SCALE, WHITE);

        Vector2 bgTwoPos = {0.f, bgY - bg.height * SCALE};
        DrawTextureEx(bg, bgTwoPos, 0.f, SCALE, WHITE);

        EndDrawing();
    }

    UnloadTexture(bg);
    CloseWindow();

    return 0;
}