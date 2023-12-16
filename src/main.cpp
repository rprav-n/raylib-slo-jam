#include <cstdio>
#include <vector>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;
const float SCALE = 4.f;
const float BULLET_OFFSET_BOUND = 50.f;

class Booster
{
public:
    Texture2D texture = LoadTexture("./assets/graphics/booster/small/sheet.png");
    int frame = 0;
    const int maxFrame = 4;
    float width = texture.width / maxFrame;
    float height = (float)texture.height;
    Rectangle source = Rectangle{0.f, 0.f, texture.width / 4.f, (float)texture.height};
    Rectangle dest = Rectangle{100.f, 100.f, width *SCALE, height *SCALE};
    Vector2 origin = {};
    float updateTime = 1.f / 16.f;
    float runningTime = 0.f;
    float rotation = 0.f;
    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Booster()
    {
        scaledWidth = width * SCALE;
        scaledHeight = height * SCALE;

        origin = {scaledWidth / 2.f,
                  scaledHeight / 2.f - 6.f * SCALE};
    }

    void Update(double dt, Vector2 pos, float rot)
    {
        rotation = rot;
        dest.x = pos.x;
        dest.y = pos.y;

        runningTime += dt;
        if (runningTime >= updateTime)
        {
            runningTime = 0.f;
            frame++;
            if (frame > maxFrame)
            {
                frame = 0;
            }
        }
    }

    void Draw()
    {
        source.x = frame * width;
        DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
    }
};

class Bullet
{
public:
    Texture2D texture;
    Rectangle rect = {};
    Vector2 position = {0.f, 0.f};
    Rectangle dest = {};
    Vector2 origin = {};
    float rotation = 0.f;
    int speed = 800;
    Vector2 direction = {};

    Bullet(Texture txt, Vector2 pos, Vector2 dir, float rot)
    {
        texture = txt;
        rect = Rectangle{0.f, 0.f, (float)texture.width, (float)texture.height};
        dest = Rectangle{0.f, 0.f, texture.width * SCALE, texture.height * SCALE};
        origin = {texture.width * SCALE / 2.f, texture.height * SCALE / 2.f};
        position = pos;
        direction = dir;
        rotation = rot;
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
        position.x += direction.x * speed * dt;
        position.y += direction.y * speed * dt;

        dest.x = position.x;
        dest.y = position.y;
    }

    void Draw()
    {
        // DrawTextureEx(texture, position, 0.f, SCALE, WHITE);
        DrawTexturePro(texture, rect, dest, origin, rotation, WHITE);
    }
};

class Player
{
public:
    Texture2D texture = LoadTexture("./assets/graphics/ships/green_ship.png");
    Texture2D red_bullet = LoadTexture("./assets/graphics/bullets/red_bullet.png");

    const int frame = 1;
    float acceleration = 10.f;
    float speed = 5.f;
    Vector2 velocity = {0.0f, 0.0f};
    float rotation = 0.f;
    float rotationSpeed = 200.0f;

    float width = 0.f;
    float height = 0.f;

    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Rectangle source = Rectangle{texture.width / 3.f, 0.f, texture.width / 3.f, (float)texture.height};
    Vector2 position = {100.f, 100.f};
    Rectangle dest = Rectangle{position.x, position.y, source.width *SCALE, (float)source.height *SCALE};
    Vector2 centerOrigin = {};
    Vector2 topLeftOrigin = {};
    Vector2 boosterPos = {};
    Vector2 origin = {};
    vector<Bullet> bullets;
    Booster booster = Booster();

    Player(Vector2 pos)
    {
        position = pos;
        width = texture.width / 3.f;
        height = texture.height;

        scaledWidth = width * SCALE;
        scaledHeight = height * SCALE;

        origin = {scaledWidth / 2.f,
                  scaledHeight / 2.f};
    }

    Vector2 GetMovementDirection()
    {
        Vector2 movement_direction = {};
        // if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        //     movement_direction.x = -1;
        // if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        //     movement_direction.x = 1;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            movement_direction.y = -1;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            movement_direction.y = 1;

        return Vector2Normalize(movement_direction);
    }

    void Update(double dt)
    {

        Vector2 direction = GetMovementDirection(); // normalized direction vector
        if (IsKeyPressed(KEY_SPACE))
        {
            ShootBullet();
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            rotation -= rotationSpeed * dt;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            rotation += rotationSpeed * dt;
        }

        // rotation = Clamp(rotation, -360.0f, 360.0f);
        if (rotation < -360.f || rotation > 360.f)
        {
            rotation = 0.f;
        }

        Vector2 rotatedDirection = Vector2Rotate(direction, DEG2RAD * rotation);

        Vector2 targetVelocity = {rotatedDirection.x * speed, rotatedDirection.y * speed};
        velocity = Vector2MoveTowards(velocity, targetVelocity, acceleration * dt);
        position = Vector2Add(position, velocity);

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

        CheckCollisionBounds();

        topLeftOrigin.x = position.x - scaledWidth / 2.f;
        topLeftOrigin.y = position.y - scaledHeight / 2.f;

        centerOrigin.x = topLeftOrigin.x + scaledWidth / 2.f;
        centerOrigin.y = topLeftOrigin.y + scaledHeight / 2.f;

        dest.x = position.x;
        dest.y = position.y;

        boosterPos = {position.x, position.y + scaledHeight / 2.f};

        booster.Update(dt, position, rotation);
    }

    void CheckCollisionBounds()
    {
        if (position.x <= scaledWidth / 2.f)
        {
            position.x = 0 + scaledWidth / 2.f;
        }
        if (position.x + scaledWidth / 2.f >= WINDOW_WIDTH)
        {
            position.x = WINDOW_WIDTH - scaledWidth / 2.f;
        }
    }

    void Draw()
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].Draw();
        }
        DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
        booster.Draw();
    }

    void ShootBullet()
    {
        Vector2 bulletDirection = Vector2Rotate({0, -1}, DEG2RAD * rotation);
        Bullet bullet = Bullet(red_bullet, centerOrigin, bulletDirection, rotation);
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