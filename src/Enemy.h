#pragma once
#include "raylib.h"
#include "Settings.h"
#include "Booster.h"

class Enemy
{

private:
    Texture2D texture = LoadTexture("./assets/graphics/enemies/basic_enemy.png");
    Texture2D boosterTexture = LoadTexture("./assets/graphics/booster/small.png");
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

public:
    Enemy(Vector2 spawnPosition);
    void Update(float dt, Vector2 playerPosition, float rot);
    void Draw();
    bool CheckCollisionWithBullet(Rectangle bulletRect);

    bool IsQueueFree() const
    {
        return queueFree;
    };
    void SetQueueFree(bool val)
    {
        queueFree = val;
    };
};