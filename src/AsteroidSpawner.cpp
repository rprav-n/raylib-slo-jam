#include "AsteroidSpawner.h"

void AsteroidSpawner::SpawnAsteroid()
{
    float xPos = GetRandomValue(-100, Settings::WINDOW_WIDTH + 100);
    float yPos = -50.f;
    float xDir = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;

    int randomNum = rand() % 2;
    int type = 0;

    Texture2D txtr;
    if (randomNum == 1)
    {
        txtr = bigAsteroidTexture;
        type = 1;
    }
    else
    {
        txtr = smallAsteroidTexture;
        type = 0;
    }

    Asteroid newAsteroid = Asteroid(txtr, Vector2{xPos, yPos}, Vector2{xDir, 1.f}, type);
    asteroids.push_back(newAsteroid);
}

void AsteroidSpawner::Update()
{
    double dt = GetFrameTime();
    currentTimer += dt;

    if (currentTimer >= spawnTime)
    {
        currentTimer = 0.f;
        spawnTime = GetRandomValue(3, 8);
        SpawnAsteroid();
    }

    for (int i = 0; i < asteroids.size(); i++)
    {
        asteroids[i].Update();
    }

    CheckBounds();

    for (int i = 0; i < asteroids.size();)
    {
        Asteroid a = asteroids[i];
        if (a.IsQueueFree())
        {
            asteroids.erase(asteroids.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void AsteroidSpawner::CheckBounds()
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        Asteroid a = asteroids[i];
        if (a.GetYPos() > Settings::WINDOW_HEIGHT + 50)
        {
            asteroids[i].SetQueueFree(true);
        }
    }
}

void AsteroidSpawner::Draw()
{
    for (int i = 0; i < asteroids.size(); i++)
    {
        asteroids[i].Draw();
    }
}