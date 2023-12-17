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
    Vector2 spawnPosition = {};
    const float margin = 100.0f;

    if (GetRandomValue(0, 1) == 0)
    {
        spawnPosition.x = (GetRandomValue(0, 1) == 0) ? -margin : Settings::WINDOW_WIDTH + margin;
        spawnPosition.y = GetRandomValue(-margin, Settings::WINDOW_HEIGHT + margin);
    }
    else
    {
        spawnPosition.x = GetRandomValue(-margin, Settings::WINDOW_WIDTH + margin);
        spawnPosition.y = (GetRandomValue(0, 1) == 0) ? -margin : Settings::WINDOW_HEIGHT + margin;
    }

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
