#include <cstdio>
#include <vector>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;
const float SCALE = 4.f;
const float BULLET_OFFSET_BOUND = 50.f;

class Bullet
{
public:
    Texture2D texture;
    Rectangle rect = {};
    Vector2 position = {0.f, 0.f};
    Rectangle dest = {};
    Vector2 origin = {};
    int speed = 400;
    float direction = 0.f;

    Bullet(Texture txt, Vector2 pos, float dir)
    {
        texture = txt;
        rect = Rectangle{0.f, 0.f, (float)texture.width, (float)texture.height};
        dest = Rectangle{0.f, 0.f, texture.width * SCALE, texture.height * SCALE};
        origin = {texture.width * SCALE / 2.f, texture.height * SCALE / 2.f};
        position = pos;
        direction = dir;
    }

    bool IsOutOfBounds()
    {
        if (position.y < 0 || position.y > WINDOW_HEIGHT + BULLET_OFFSET_BOUND || position.x < -BULLET_OFFSET_BOUND || position.x > WINDOW_WIDTH + BULLET_OFFSET_BOUND)
        {
            return true;
        }
        return false;
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

class Player
{
public:
    Texture2D texture = LoadTexture("./assets/graphics/ships/green_ship.png");
    Texture2D red_bullet = LoadTexture("./assets/graphics/bullets/red_bullet.png");
    int frame = 1;
    int speed = 250;
    float width = 0.f;
    float height = 0.f;

    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Rectangle source = Rectangle{texture.width / 3.f, 0.f, texture.width / 3.f, (float)texture.height};
    Vector2 position = {100.f, 100.f};
    Rectangle dest = Rectangle{position.x, position.y, source.width *SCALE, (float)source.height *SCALE};
    Vector2 origin = {};
    Vector2 centerOrigin = {};
    vector<Bullet> bullets;

    Player(Vector2 pos)
    {
        position = pos;
        width = texture.width / 3.f;
        height = texture.height;

        scaledWidth = width * SCALE;
        scaledHeight = height * SCALE;
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

        if (IsKeyPressed(KEY_SPACE))
        {
            ShootBullet();
        }

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

        // position = Vector2MoveTowards(position, Vector2{position.x + direction.x * speed * (float)dt, position.y + direction.y * speed * (float)dt}, speed * dt);

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Update(dt);
        }

        // Remove bullet if it goes beyound the screen
        for (int i = 0; i < bullets.size();)
        {
            Bullet b = bullets[i];
            if (b.IsOutOfBounds())
            {
                bullets.erase(bullets.begin() + i);
            }
            else
            {
                ++i;
            }
        }

        // printf("bullets.size() %lu\n", bullets.size());

        CheckCollisionBounds();

        dest.x = position.x;
        dest.y = position.y;

        centerOrigin.x = position.x + (scaledWidth / 2.f);
        centerOrigin.y = position.y + (scaledHeight / 2.f);
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
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw();
        }
        DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
    }

    void ShootBullet()
    {
        Bullet bullet = Bullet(red_bullet, centerOrigin, -1.f);
        bullets.push_back(bullet);
    }
};

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Edge Of Void");

    Texture2D bg = LoadTexture("./assets/graphics/environment/bg.png");
    const int bgMoveSpeed = 200;
    float bgY = 0.f;

    Player player = Player(Vector2{WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    // Bullet bullet = Bullet(Vector2{WINDOW_WIDTH / 2, 500.f}, -1.f);

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

        DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(bg);
    CloseWindow();

    return 0;
}