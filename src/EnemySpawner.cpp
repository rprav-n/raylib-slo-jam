#include "EnemySpawner.h"

void EnemySpawner::Update(Vector2 playerPosition, float playerRotation)
{
    const float dt = GetFrameTime();
    if (shouldSpawn)
    {
        currentTimer += dt;
    }

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
    const float margin = 30.0f;

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

    int randomEnemyIndex = GetRandomValue(0, enemyTextures.size() - 1);
    float speed = 100.f;
    float shootSpanwnTimer = 5.f;

    switch (randomEnemyIndex)
    {
    case 0: // basic_enemy_1
        speed = basicEnemyOneSpeed;
        shootSpanwnTimer = 1.f;
        break;
    case 1: // basic_enemy_2
        speed = basicEnemyTwoSpeed;
        break;
    case 2: // basic_enemy_3
        speed = basicEnemyThreeSpeed;
        break;
    case 3: // basic_enemy_4
        speed = basicEnemyFourSpeed;
        break;
    case 4: // basic_enemy_5
        speed = basicEnemyFiveSpeed;
        shootSpanwnTimer = GetRandomValue(2, 3);
        break;
    case 5: // m_e_1
        speed = m_e_1;
        shootSpanwnTimer = GetRandomValue(2, 8);
        break;
    case 6: // m_e_2
        speed = m_e_1;
        shootSpanwnTimer = GetRandomValue(2, 8);
        break;

    default:
        break;
    }

    Enemy enemy = Enemy(enemyTextures[randomEnemyIndex], spawnPosition, speed, randomEnemyIndex, shootSpanwnTimer);
    enemies.push_back(enemy);
}

void EnemySpawner::Draw()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}

void EnemySpawner::DecreaseSpawnTimer()
{
    spawnTime -= 0.3f;
    if (spawnTime <= 1.f)
    {
        spawnTime = 1.f;
    }
    basicEnemyOneSpeed += 100 * 0.12f;
    basicEnemyTwoSpeed += 100 * 0.12f;
    basicEnemyThreeSpeed += 100 * 0.12f;
    basicEnemyFourSpeed += 100 * 0.12f;
    basicEnemyFiveSpeed += 100 * 0.12f;
}