#pragma once
#include <vector>
#include <cstdio>
#include "raylib.h"
#include "Enemy.h"

#include "Settings.h"
#include <vector>

using namespace std;

class EnemySpawner
{
public:
    void Update(Vector2 playerPosition, float playerRotation);
    void SpawnEnemy();
    void Draw();
    void DecreaseSpawnTimer();
    vector<Enemy> enemies;

private:
    float spawnTime = 4.f;
    float currentTimer = 0.f;
    Texture2D basicEnemy1 = LoadTexture("./assets/graphics/enemies/basic_enemy_1.png");
    Texture2D basicEnemy2 = LoadTexture("./assets/graphics/enemies/basic_enemy_2.png");
    Texture2D basicEnemy3 = LoadTexture("./assets/graphics/enemies/basic_enemy_3.png");
    vector<Texture2D> enemyTextures = {basicEnemy1, basicEnemy2, basicEnemy3};
};