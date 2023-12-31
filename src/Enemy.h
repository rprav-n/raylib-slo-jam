#pragma once
#include "raylib.h"
#include "Settings.h"
#include "Booster.h"
#include "Bullet.h"
#include "Helper.h"
#include <vector>

using namespace std;

class Enemy
{

private:
    Texture2D texture = LoadTexture("./assets/graphics/enemies/basic_enemy_1.png");
    Texture2D boosterTexture = LoadTexture("./assets/graphics/booster/small.png");
    Texture2D greenBullet = LoadTexture("./assets/graphics/bullets/green_bullet.png");
    float scaledWidth = texture.width * Settings::SCALE;
    float scaledHeight = texture.height * Settings::SCALE;
    Rectangle source = {0.f, 0.f, (float)texture.width, (float)texture.height};
    Vector2 position = {100.f, 100.f};
    Rectangle dest = {position.x, position.y, scaledWidth, scaledHeight};
    Vector2 origin = {scaledWidth / 2.f, scaledHeight / 2.f};
    float speed = 100.f;
    float rotation = 0.f;
    Vector2 boosterPos = {};

    Booster booster = Booster(boosterTexture, Vector2{0.f, -6.f});

    bool queueFree = false;

    int health = 1;

    // flicker variables
    float flickerDuration = 1.f;
    float flickerTimer = 0.0f;
    bool isFlickering = false;

public:
    Enemy(Texture2D txtr, Vector2 spawnPosition, float spd, int type, float shootDelayTimer);
    Helper helper = Helper();
    void Update(float dt, Vector2 playerPosition, float rot);
    void Draw();
    void ReduceHealth();
    void ShootBullet();
    void KnockBack();

    int enemyType = 0;
    int score = 0;

    Vector2 GetPosition();

    bool IsQueueFree()
    {
        return queueFree;
    };
    void SetQueueFree(bool val)
    {
        queueFree = val;
    };

    int GetHealth()
    {
        return health;
    };

    Vector2 centerPoint = {};
    float radius = 14.f;

    vector<Bullet> bullets = {};

    // Bullet
    int bulletSpeed = 400;
    bool canAutoShoot = false;
    float shootSpanwnTimer = 5.f;
    float shootTimer = 0.0f;
};