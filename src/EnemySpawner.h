#pragma once
#include <vector>
#include <cstdio>
#include "raylib.h"
#include "Enemy.h"

#include "Settings.h"

using namespace std;

class EnemySpawner
{
public:
    void Update(Vector2 playerPosition, float playerRotation);
    void SpawnEnemy();
    void Draw();
    vector<Enemy> enemies;

private:
    float spawnTime = 2.f;
    float currentTimer = 0.f;
};