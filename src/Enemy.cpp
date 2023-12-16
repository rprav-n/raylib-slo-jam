#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

void Enemy::Update(double dt, Vector2 playerPosition, float rot)
{
    position = Vector2MoveTowards(position, playerPosition, speed * dt);

    rotation = Vector2Angle(position, playerPosition) * RAD2DEG - 90;

    dest.x = position.x;
    dest.y = position.y;
}

void Enemy::Draw()
{
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}
