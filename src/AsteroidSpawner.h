#pragma once
#include "raylib.h"
#include <vector>
#include "Asteroid.h"
#include "raymath.h"
#include "Settings.h"

using namespace std;

class AsteroidSpawner
{
public:
    void SpawnAsteroid();
    void Update();
    void Draw();
    vector<Asteroid> asteroids;

private:
    Texture2D bigAsteroidTexture = LoadTexture("./assets/graphics/environment/asteroid_big.png");
    float spawnTime = 1.f;
    float currentTimer = 0.f;
    bool IsQueueFree = false;
};