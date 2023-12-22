#include "AsteroidSpawner.h"

void AsteroidSpawner::SpawnAsteroid()
{
    float xPos = GetRandomValue(50, Settings::WINDOW_WIDTH);
    float yPos = -50.f;

    Asteroid newAsteroid = Asteroid(bigAsteroidTexture, Vector2{xPos, yPos}, Vector2{0.f, 1.f});
    asteroids.push_back(newAsteroid);
}

void AsteroidSpawner::Update()
{
    double dt = GetFrameTime();
    currentTimer += dt;

    if (currentTimer >= spawnTime)
    {
        currentTimer = 0.f;
        SpawnAsteroid();
    }

    for (int i = 0; i < asteroids.size(); i++)
    {
        asteroids[i].Update();
    }
}

void AsteroidSpawner::Draw()
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        asteroids[i].Draw();
    }
}