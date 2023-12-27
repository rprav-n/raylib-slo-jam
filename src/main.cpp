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
#include "Transition.h"
#include "AbilityScreen.h"
#include <vector>

using namespace std;

class Game
{
private:
    Texture2D crossHairTexture = LoadTexture("./assets/graphics/ui/cross_hair.png");
    Texture2D explosionTexture = LoadTexture("./assets/graphics/explosion/red.png");
    vector<Explosion> explosions;

    Player player = Player(Vector2{Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f});

    EnemySpawner enemySpawner = EnemySpawner();
    AsteroidSpawner asteroidSpawner = AsteroidSpawner();
    SoundManager soundManager = SoundManager();

    MainScreen mainScreen = MainScreen();

    Transition transition = Transition(1.f);
    AbilityScreen abilityScreen = AbilityScreen();

public:
    Game()
    {
        HideCursor();
    };
    Vector2 GetPlayerPositon()
    {
        return player.GetPosition();
    };
    void Update()
    {
        soundManager.UpdateMusic();

        if (mainScreen.isPlayPressed())
        {
            if (transition.IsComplete())
            {
                GameStarted();
            }
            else
            {
                transition.Update();
            }
        }
        else
        {
            mainScreen.Update();
        }
    };

    void Draw()
    {
        if (mainScreen.isPlayPressed())
        {

            if (transition.IsComplete())
            {
                asteroidSpawner.Draw();
                enemySpawner.Draw();

                for (int i = 0; i < explosions.size(); i++)
                {
                    explosions[i].Draw();
                }

                player.Draw();

                if (player.showAbilityScreen)
                {
                    abilityScreen.Draw();
                }
            }
            else
            {
                transition.Draw();
            }
        }
        else
        {
            mainScreen.Draw();
        }

        // Draw mouse cursor - cross hair
        DrawTextureEx(crossHairTexture, GetMousePosition(), 0.f, Settings::SCALE, WHITE);
    }

    void GameStarted()
    {
        if (player.showAbilityScreen)
        {
            // TODO
            // Control all the ability clicks here
            if (IsKeyPressed(KEY_ONE))
            {
                player.canAutoShoot = true;
                enemySpawner.DecreaseSpawnTimer();
                player.showAbilityScreen = false;
            }
            else if (IsKeyPressed(KEY_TWO))
            {
                player.hasDoubleGun = true;
                enemySpawner.DecreaseSpawnTimer();
                player.showAbilityScreen = false;
            }
            else if (IsKeyPressed(KEY_THREE))
            {
                player.hasDash = true;
                enemySpawner.DecreaseSpawnTimer();
                player.showAbilityScreen = false;
            }
            else if (IsKeyPressed(KEY_FOUR))
            {
                // TODO reduce by only 10%
                player.shootSpanwnTimer -= 0.1f;
                enemySpawner.DecreaseSpawnTimer();
                player.showAbilityScreen = false;
            }
            else if (IsKeyPressed(KEY_FIVE))
            {
                // Get full health
                player.GetFullHealth();
                player.showAbilityScreen = false;
                enemySpawner.DecreaseSpawnTimer();
            }
            else if (IsKeyPressed(KEY_SIX))
            {
                // Get Shield or Full Sheild
                player.hasShied = true;
                player.showAbilityScreen = false;
                enemySpawner.DecreaseSpawnTimer();
            }
            else if (IsKeyPressed(KEY_SEVEN))
            {
                // Shoot 3 Burst Bullets
                player.hasBurstBullet = true;
                player.showAbilityScreen = false;
                enemySpawner.DecreaseSpawnTimer();
            }

            return;
        }
        const float dt = GetFrameTime();
        player.Update(dt);

        enemySpawner.Update(player.GetPosition(), player.GetRotation());
        asteroidSpawner.Update();

        // collision b/w player bullet and enemy
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
                        player.UpdateExpBarWidth();
                    }
                }
            }
        }

        // collision b/w player ship and enemy ship
        for (int i = 0; i < enemySpawner.enemies.size(); i++)
        {
            Enemy e = enemySpawner.enemies[i];
            if (CheckCollisionCircles(player.centerPoint, player.radius, e.centerPoint, e.radius))
            {
                player.ReduceHealth();
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

    Camera2D camera = {};
    camera.target = Vector2{Settings::WINDOW_WIDTH / 2.0f, Settings::WINDOW_HEIGHT / 2.0f};
    camera.offset = Vector2{Settings::WINDOW_WIDTH / 2.0f, Settings::WINDOW_HEIGHT / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Game game = Game();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        game.Update();
        // camera.target = game.GetPlayerPositon();

        BeginDrawing();
        ClearBackground(BLACK);
        {
            BeginMode2D(camera);
            {
                game.Draw();
                DrawFPS(10, Settings::WINDOW_HEIGHT - 20);
            }
            EndMode2D();
        }

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}