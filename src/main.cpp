#include <cstdio>

#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "Asteroid.h"
#include "AsteroidSpawner.h"
#include "MainScreen.h"
#include <vector>

using namespace std;

class Game
{
private:
    Texture2D explosionTexture = LoadTexture("./assets/graphics/explosion/red.png");
    vector<Explosion> explosions;

    Player player = Player(Vector2{Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f});

    EnemySpawner enemySpawner = EnemySpawner();
    AsteroidSpawner asteroidSpawner = AsteroidSpawner();
    SoundManager soundManager = SoundManager();

    MainScreen mainScreen = MainScreen();

public:
    void Update()
    {
        soundManager.UpdateMusic();

        if (mainScreen.isPlayPressed())
        {
            GameStarted();
        }
        else
        {
            mainScreen.Update();
        }
    }

    void Draw()
    {
        if (mainScreen.isPlayPressed())
        {
            asteroidSpawner.Draw();
            enemySpawner.Draw();

            for (int i = 0; i < explosions.size(); i++)
            {
                explosions[i].Draw();
            }

            player.Draw();
        }
        else
        {
            mainScreen.Draw();
        }
    }

    void GameStarted()
    {
        const float dt = GetFrameTime();
        player.Update(dt);

        enemySpawner.Update(player.GetPosition(), player.GetRotation());
        asteroidSpawner.Update();

        for (int i = 0; i < player.bullets.size(); i++)
        {
            Bullet b = player.bullets[i];
            for (int j = 0; j < enemySpawner.enemies.size(); j++)
            {
                Enemy e = enemySpawner.enemies[j];
                if (CheckCollisionCircles(b.centerPoint, b.radius, e.centerPoint, e.radius))
                {
                    player.bullets[i].SetQueueFree(true);
                    enemySpawner.enemies[j].ReduceHealth();

                    if (enemySpawner.enemies[j].GetHealth() == 0)
                    {
                        enemySpawner.enemies[j].SetQueueFree(true);
                        SpanwExplosion(e.GetPosition());
                        soundManager.PlayExplosionSfx();
                    }
                }
            }
        }

        // when player and enemy ship collides
        for (int i = 0; i < enemySpawner.enemies.size(); i++)
        {
            Enemy e = enemySpawner.enemies[i];
            if (CheckCollisionCircles(player.centerPoint, player.radius, e.centerPoint, e.radius))
            {
                player.UpdatePlayerHealthProgressWidth();
                // TODO
                // Reduce player health
                // Reduce enemy health
                SpanwExplosion(e.GetPosition());
                enemySpawner.enemies[i].SetQueueFree(true);
                soundManager.PlayExplosionSfx();
            }
        }

        for (int i = 0; i < explosions.size(); i++)
        {
            explosions[i].Update(dt);
        }

        RemoveExplosion();
    }

    void SpanwExplosion(Vector2 position)
    {
        Explosion explosion = Explosion(explosionTexture, position);
        explosions.push_back(explosion);
    }

    void RemoveExplosion()
    {
        for (int i = 0; i < explosions.size();)
        {
            Explosion e = explosions[i];
            if (e.IsQueueFree())
            {
                explosions.erase(explosions.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }
};

int main()
{
    InitWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, "Edge Of Void");
    InitAudioDevice();

    Texture2D bg = LoadTexture("./assets/graphics/environment/bg.png");
    const int bgMoveSpeed = 200;
    float bgY = 0.f;

    Game game = Game();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        bgY += bgMoveSpeed * dt;
        if (bgY >= bg.height * Settings::SCALE)
        {
            bgY = 0.f;
        }

        Vector2 bgOnePos = {0.f, bgY};
        DrawTextureEx(bg, bgOnePos, 0.f, Settings::SCALE, WHITE);

        Vector2 bgTwoPos = {0.f, bgY - bg.height * Settings::SCALE};
        DrawTextureEx(bg, bgTwoPos, 0.f, Settings::SCALE, WHITE);

        game.Update();
        game.Draw();

        DrawFPS(10, Settings::WINDOW_HEIGHT - 20);

        EndDrawing();
    }

    UnloadTexture(bg);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}