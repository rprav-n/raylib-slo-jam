#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

void Enemy::Update(double dt, Vector2 playerPosition, float rot)
{

    // position = Vector2MoveTowards(position, playerPosition, speed * dt);

    Vector2 direction = Vector2Subtract(position, playerPosition);

    // rotation = atan2(direction.y, direction.x) * RAD2DEG;
    rotation = Vector2Angle(position, playerPosition) * RAD2DEG;

    printf("rotation %f direction %f %f\n", rotation, direction.x, direction.y);

    DrawLine(position.x, position.y, playerPosition.x, playerPosition.y, RED);

    dest.x = position.x;
    dest.y = position.y;
}

void Enemy::Draw()
{
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
    DrawRectangleLines(position.x - scaledWidth / 2.f, position.y - scaledHeight / 2.f, scaledWidth, scaledHeight, RED);
}
