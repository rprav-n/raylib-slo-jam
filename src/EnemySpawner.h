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
    float basicEnemyOneSpeed = 50.f;
    float basicEnemyTwoSpeed = 75.f;
    float basicEnemyThreeSpeed = 50.f;
    float basicEnemyFourSpeed = 80.f;
    float basicEnemyFiveSpeed = 30.f;

    // Medium Enemies
    float m_e_1 = 20.f;
    float m_e_2 = 20.f;

private:
    bool shouldSpawn = true;
    float spawnTime = 2.5f;
    float currentTimer = 0.f;
    Texture2D basicEnemy1 = LoadTexture("./assets/graphics/enemies/basic_enemy_1.png");
    Texture2D basicEnemy2 = LoadTexture("./assets/graphics/enemies/basic_enemy_2.png");
    Texture2D basicEnemy3 = LoadTexture("./assets/graphics/enemies/basic_enemy_3.png");
    Texture2D basicEnemy4 = LoadTexture("./assets/graphics/enemies/basic_enemy_4.png");
    Texture2D basicEnemy5 = LoadTexture("./assets/graphics/enemies/basic_enemy_5.png");

    Texture2D mediumEnemy1 = LoadTexture("./assets/graphics/enemies/medium_enemy_1.png");
    Texture2D mediumEnemy2 = LoadTexture("./assets/graphics/enemies/medium_enemy_2.png");

    vector<Texture2D> enemyTextures = {basicEnemy1, basicEnemy2, basicEnemy3, basicEnemy4, basicEnemy5, mediumEnemy1, mediumEnemy2};

    // vector<Texture2D> mediumEnemyTextures = {mediumEnemy1};
};