#include "EnemySpawner.h"

void EnemySpawner::Update(Vector2 playerPosition, float playerRotation)
{
    const float dt = GetFrameTime();
    currentTimer += dt;

    if (currentTimer >= spawnTime)
    {
        currentTimer = 0.f;
        SpawnEnemy();
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update(dt, playerPosition, playerRotation);
    }

    for (int i = 0; i < enemies.size();)
    {
        Enemy e = enemies[i];
        if (e.IsQueueFree())
        {
            enemies.erase(enemies.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void EnemySpawner::SpawnEnemy()
{
    Vector2 spawnPosition = {(float)GetRandomValue(0, Settings::WINDOW_WIDTH), (float)GetRandomValue(0, Settings::WINDOW_HEIGHT)};
    Enemy enemy = Enemy(spawnPosition);
    enemies.push_back(enemy);
}

void EnemySpawner::Draw()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}
