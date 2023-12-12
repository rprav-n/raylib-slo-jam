#include <iostream>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;
const float SCALE = 4.f;

class Player
{
public:
    Texture2D texture = LoadTexture("./assets/graphics/ships/green_ship.png");
    int frame = 1;
    int speed = 100;
    float width = 0.f;
    float height = 0.f;

    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Rectangle source = Rectangle{texture.width / 3.f, 0.f, texture.width / 3.f, (float)texture.height};
    Vector2 position = {100.f, 100.f};
    Rectangle dest = Rectangle{position.x, position.y, source.width *SCALE, (float)source.height *SCALE};
    Vector2 origin = {};

    Player(Vector2 pos)
    {
        position = pos;
        width = texture.width / 3.f;
        height = texture.height;

        scaledWidth = width * SCALE;
        scaledHeight = height * SCALE;

        // origin = {width * SCALE / 2.f, height * SCALE / 2.f};
    }

    void Update(double dt)
    {
        Vector2 direction = {};
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            direction.x = -1;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            direction.x = 1;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            direction.y = -1;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            direction.y = 1;

        direction = Vector2Normalize(direction);

        if (direction.x < 0)
            frame = 0;
        if (direction.x > 0)
            frame = 2;
        if (direction.x == 0)
            frame = 1;

        source.x = width * frame;

        position.x += direction.x * speed * dt;
        position.y += direction.y * speed * dt;

        CheckCollisionBounds();

        dest.x = position.x;
        dest.y = position.y;
    }

    void CheckCollisionBounds()
    {
        if (position.x <= 0)
        {
            position.x = 0;
        }
        if (position.x + scaledWidth >= WINDOW_WIDTH)
        {
            position.x = WINDOW_WIDTH - scaledWidth;
        }
    }

    void Draw()
    {
        DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
    }
};

class Bullet
{
public:
    Texture2D texture = LoadTexture("./assets/graphics/bullets/red_bullet.png");
    Rectangle rect = Rectangle{0.f, 0.f, (float)texture.width, (float)texture.height};
    Vector2 position = {0.f, 0.f};
    Rectangle dest = Rectangle{0.f, 0.f, texture.width *SCALE, texture.height *SCALE};
    Vector2 origin = {texture.width * SCALE / 2.f, texture.height *SCALE / 2.f};
    int speed = 100;
    float direction = 0.f;

    Bullet(Vector2 pos, float dir)
    {
        position = pos;
        direction = dir;
    }

    void Update(float dt)
    {
        position.y += direction * speed * dt;

        dest.x = position.x;
        dest.y = position.y;
    }

    void Draw()
    {
        // DrawTextureEx(texture, position, 0.f, SCALE, WHITE);
        DrawTexturePro(texture, rect, dest, origin, 0.f, WHITE);
    }
};

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Edge Of Void");

    Texture2D bg = LoadTexture("./assets/graphics/environment/bg.png");
    const int bgMoveSpeed = 200;
    float bgY = 0.f;

    Player player = Player(Vector2{WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    Bullet bullet = Bullet(Vector2{WINDOW_WIDTH / 2, 500.f}, -1.f);

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

        player.Update(dt);
        player.Draw();

        bullet.Update(dt);
        bullet.Draw();

        DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(bg);
    CloseWindow();

    return 0;
}