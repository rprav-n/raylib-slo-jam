#include <cstdio>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Game
{
private:
    Player player = Player(Vector2{Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f});
    Enemy enemy = Enemy();

public:
    void Update()
    {
        const float dt = GetFrameTime();
        player.Update(dt);
        enemy.Update(dt, player.GetPosition(), player.GetRotation());
    }

    void Draw()
    {
        player.Draw();
        enemy.Draw();
    }
};

int main()
{
    InitWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, "Edge Of Void");

    Texture2D bg = LoadTexture("./assets/graphics/environment/bg.png");
    const int bgMoveSpeed = 200;
    float bgY = 0.f;

    Game game = Game();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        bgY += bgMoveSpeed * dt;
        if (bgY >= bg.height * Settings::SCALE)
        {
            bgY = 0.f;
        }

        Vector2 bgOnePos = {0.f, bgY};
        DrawTextureEx(bg, bgOnePos, 0.f, Settings::SCALE, WHITE);

        Vector2 bgTwoPos = {0.f, bgY - bg.height * Settings::SCALE};
        DrawTextureEx(bg, bgTwoPos, 0.f, Settings::SCALE, WHITE);

        game.Update();
        game.Draw();

        DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(bg);
    CloseWindow();

    return 0;
}