#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

Enemy::Enemy(Texture2D txtr, Vector2 spawnPosition, float spd, int type)
{
    texture = txtr;
    position = spawnPosition;

    scaledWidth = texture.width * Settings::SCALE;
    scaledHeight = texture.height * Settings::SCALE;
    source = {0.f, 0.f, (float)texture.width, (float)texture.height};
    dest = {position.x, position.y, scaledWidth, scaledHeight};
    origin = {scaledWidth / 2.f, scaledHeight / 2.f};
    speed = spd;
    enemyType = type;

    switch (enemyType)
    {
    case 0: // basic_enemy_1
        health = 1;
        break;
    case 1: // basic_enemy_2
        health = 1;
        break;
    case 2: // basic_enemy_3
        health = 2;
        break;

    default:
        break;
    }
}

void Enemy::Update(float dt, Vector2 playerPosition, float rot)
{
    position = Vector2MoveTowards(position, playerPosition, speed * dt);

    rotation = Vector2Angle(position, playerPosition) * RAD2DEG - 90;

    dest.x = position.x;
    dest.y = position.y;

    boosterPos = {position.x, position.y};

    booster.Update(dt, boosterPos, rotation + 180);

    centerPoint = {position.x, position.y};

    if (isFlickering)
    {
        flickerTimer += GetFrameTime();
    }
    if (flickerTimer >= flickerDuration)
    {

        isFlickering = false;
        flickerTimer = 0.0f;
    }
}

void Enemy::Draw()
{
    booster.Draw();
    if (!isFlickering)
    {
        DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
    }
    else
    {
        if (((int)(flickerTimer * 10) % 2) == 0)
        {
            DrawTexturePro(texture, source, dest, origin, rotation, RED);
        }
        else
        {
            DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
        }
    }
}

Vector2 Enemy::GetPosition()
{
    return position;
}

void Enemy::ReduceHealth()
{
    health -= 1;
    printf("health %d\n", health);
    // Flicker enemy with white for 0.2s
    isFlickering = true;
}

void Enemy::FlickerEnemy()
{
}