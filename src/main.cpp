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

struct Particle
{
    Vector2 position;
    Vector2 speed;
    Color color;
    float radius;
    float alpha;
    float size;
};

vector<Particle> particles;
vector<Color> explosionColors = {GetColor(0xfff392ff), GetColor(0xfff392ff), GetColor(0xfff392ff), GetColor(0xffa200ff), GetColor(0xffa200ff), GetColor(0xe35100ff)};

void UpdateParticles()
{
    for (auto &particle : particles)
    {
        particle.position.x += particle.speed.x;
        particle.position.y += particle.speed.y;
        particle.radius *= 0.98f; // Shrink particles over time
        particle.size *= 0.98f;   // Shrink particles over time
        // particle.alpha *= 0.98f;  // Fade particles over time
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(),
                                   [](const Particle &particle)
                                   { return particle.radius < 0.1f; }),
                    particles.end());
}

float GetRandomFloat(float min, float max)
{
    return min + (float)GetRandomValue(0, 10000) / 10000.0f * (max - min);
}

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
    bool shouldCameraShake = false;
    void SetCameraShake(bool val)
    {
        shouldCameraShake = val;
    };

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

                player.Draw();
                for (int i = 0; i < explosions.size(); i++)
                {
                    explosions[i].Draw();
                }

                if (player.showAbilityScreen)
                {
                    abilityScreen.Draw();
                }

                // Draw particles
                for (const auto &particle : particles)
                {
                    // DrawCircleV(particle.position, particle.radius, Fade(particle.color, particle.alpha / 255.0f));
                    // DrawCircleV(particle.position, particle.radius, particle.color);
                    DrawRectangleV(particle.position, Vector2{particle.size, particle.size}, particle.color);
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
        Vector2 mousePos = GetMousePosition();
        mousePos.x -= crossHairTexture.width / 2.f;
        mousePos.y -= crossHairTexture.height / 2.f;
        DrawTextureEx(crossHairTexture, mousePos, 0.f, Settings::SCALE, WHITE);
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
                player.hasBurstBullet = false;
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
                player.shootSpanwnTimer -= 0.05f;
                if (player.shootSpanwnTimer < 0.1f)
                {
                    player.shootSpanwnTimer = 0.1f;
                }
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
                player.GetFullShield();
                player.showAbilityScreen = false;
                enemySpawner.DecreaseSpawnTimer();
            }
            else if (IsKeyPressed(KEY_SEVEN))
            {
                // Shoot 3 Burst Bullets
                player.hasDoubleGun = false;
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

        // collision b/w enemies bullet and player
        for (int i = 0; i < enemySpawner.enemies.size(); i++)
        {
            for (int j = 0; j < enemySpawner.enemies[i].bullets.size(); j++)
            {
                Bullet b = enemySpawner.enemies[i].bullets[j];
                if (CheckCollisionCircles(b.centerPoint, b.radius, player.centerPoint, player.GetRadius()))
                {
                    enemySpawner.enemies[i].bullets[j].SetQueueFree(true);
                    player.ReduceHealth();

                    SpanwExplosion(b.GetPosition());
                    soundManager.PlayExplosionSfx();
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

        if (IsKeyPressed(KEY_G))
        {
            shouldCameraShake = true;
        }

        UpdateParticles();
    }

    void SpanwExplosion(Vector2 position)
    {
        Explosion explosion = Explosion(explosionTexture, position);
        explosions.push_back(explosion);
        shouldCameraShake = true;

        for (int i = 0; i < 20; ++i)
        {
            int ri = GetRandomValue(0, explosionColors.size() - 1);
            Particle particle;
            particle.position = position;
            particle.speed = {GetRandomFloat(-1, 1), GetRandomFloat(-1, 1)};
            particle.color = explosionColors[ri];
            particle.radius = (float)GetRandomValue(1, 10);
            particle.alpha = 255;
            particle.size = (float)GetRandomValue(1, 20);
            particles.push_back(particle);
        }
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

    // Background
    Texture2D bgTexture = LoadTexture("./assets/graphics/environment/bg.png");
    float width = bgTexture.width;
    float height = bgTexture.height;

    float scaledWidth = width * 6;
    float scaledHeight = height * 6;

    Rectangle source = Rectangle{0, 0, width, height};
    Rectangle destOne = Rectangle{0, -Settings::WINDOW_HEIGHT, scaledWidth, scaledHeight};
    Rectangle destTwo = Rectangle{0, 0, scaledWidth, scaledHeight};

    float bgY = 0.f;

    float shakeDuration = 0.0f;
    float shakeIntensity = 4.0f;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        bgY += dt * 400.f;

        if (bgY >= scaledHeight)
        {
            bgY = 0.f;
        }

        if (game.shouldCameraShake)
        {
            shakeDuration = 0.5f;
            shakeIntensity = GetRandomValue(1, 3);
        }

        // Camera Shake
        if (shakeDuration > 0.0f)
        {
            float offsetX = GetRandomValue(-shakeIntensity, shakeIntensity);
            float offsetY = GetRandomValue(-shakeIntensity, shakeIntensity);

            // Apply shake effect to camera target
            camera.target.x += offsetX;
            camera.target.y += offsetY;

            shakeDuration -= GetFrameTime();
            game.SetCameraShake(false);
        }
        else
        {
            camera.target = Vector2MoveTowards(camera.target, Vector2{Settings::WINDOW_WIDTH / 2.0f, Settings::WINDOW_HEIGHT / 2.0f},
                                               100 * dt);
        }

        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        {
            destTwo.y = bgY;
            destOne.y = -scaledHeight + bgY;
            DrawTexturePro(bgTexture, source, destTwo, Vector2{0, 0}, 0.f, WHITE);
            DrawTexturePro(bgTexture, source, destOne, Vector2{0, 0}, 0.f, WHITE);

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