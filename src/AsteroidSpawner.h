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
    void CheckBounds();
    vector<Asteroid> asteroids;

private:
    Texture2D bigAsteroidTexture = LoadTexture("./assets/graphics/environment/asteroid_big.png");
    Texture2D smallAsteroidTexture = LoadTexture("./assets/graphics/environment/asteroid_small.png");
    float spawnTime = 3.f;
    float currentTimer = 0.f;
    bool shoudlSpawn = false;
};