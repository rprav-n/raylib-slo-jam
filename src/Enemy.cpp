#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

Enemy::Enemy(Vector2 spawnPosition)
{
    position = spawnPosition;
}

void Enemy::Update(float dt, Vector2 playerPosition, float rot)
{
    position = Vector2MoveTowards(position, playerPosition, speed * dt);

    rotation = Vector2Angle(position, playerPosition) * RAD2DEG - 90;

    dest.x = position.x;
    dest.y = position.y;

    boosterPos = {position.x, position.y};

    booster.Update(dt, boosterPos, rotation + 180);
}

void Enemy::Draw()
{
    booster.Draw();
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}

bool Enemy::CheckCollisionWithBullet(Rectangle bulletRect)
{
    return CheckCollisionRecs(dest, bulletRect);
}