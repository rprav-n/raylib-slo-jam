#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

Enemy::Enemy(Texture2D txtr, Vector2 spawnPosition, float spd, int type, float shootDelayTimer)
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
    shootSpanwnTimer = shootDelayTimer;

    switch (enemyType)
    {
    case 0: // basic_enemy_1
        health = 1;
        score = 10;
        canAutoShoot = true;
        break;
    case 1: // basic_enemy_2
        health = 1;
        score = 25;
        break;
    case 2: // basic_enemy_3
        health = 2;
        score = 50;
        canAutoShoot = true;
        break;
    case 3: // basic_enemy_4
        health = 1;
        score = 25;
        break;
    case 4: // basic_enemy_5
        health = 3;
        score = 50;
        break;
    case 5: // m_e_1
        health = GetRandomValue(4, 8);
        score = 100;
        canAutoShoot = true;
        break;
    case 6: // m_e_2
        health = GetRandomValue(4, 8);
        score = 100;
        canAutoShoot = true;
        break;

    default:
        break;
    }

    // health = 100.f; // TODO Remove this
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

    if (canAutoShoot)
    {
        shootTimer += dt;
        if (shootTimer >= shootSpanwnTimer)
        {
            shootTimer = 0.f;
            ShootBullet();
        }
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update(dt);
    }

    // Remove bullet if it goes beyound the screen
    for (int i = 0; i < bullets.size();)
    {
        Bullet b = bullets[i];
        if (b.IsOutOfBounds() || b.IsQueueFree())
        {
            bullets.erase(bullets.begin() + i);
        }
        else
        {
            ++i;
        }
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

    for (int i = 0; i < bullets.size(); i++)
    {
        if (!bullets[i].IsQueueFree())
        {
            bullets[i].Draw();
        }
    }

    if (Settings::DEBUG)
    {
        DrawCircleV(centerPoint, radius, RED);
    }
}

Vector2 Enemy::GetPosition()
{
    return position;
}

void Enemy::ReduceHealth()
{
    health -= 1;
    isFlickering = true;
    KnockBack();
}

void Enemy::ShootBullet()
{
    Vector2 bulletDirection = Vector2Rotate({helper.GetRandomFloat(-0.5, 0.5), 1}, DEG2RAD * rotation);
    Bullet bullet = Bullet(greenBullet, position, bulletDirection, rotation, bulletSpeed, GREEN);
    bullets.push_back(bullet);
}

void Enemy::KnockBack()
{
    float rotationInRadians = DEG2RAD * rotation;
    Vector2 knockbackVector = Vector2Rotate({0.0f, -helper.GetRandomFloat(4.f, 8.f)}, rotationInRadians);
    position = Vector2Add(position, knockbackVector);
}
