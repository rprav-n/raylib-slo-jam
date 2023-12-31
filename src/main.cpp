#include <cstdio>

#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "Helper.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "Explosion.h"
#include "SoundManager.h"
#include "Asteroid.h"
#include "AsteroidSpawner.h"
#include "MainScreen.h"
#include "Transition.h"
#include "AbilityScreen.h"
#include "Ponit.h"
#include "Particle.h"
#include <vector>

using namespace std;

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

class Game
{
private:
    Font pixelFont = LoadFont("./assets/fonts/kenney_pixel.ttf");
    Texture2D crossHairTexture = LoadTexture("./assets/graphics/ui/cross_hair.png");
    Texture2D explosionTexture = LoadTexture("./assets/graphics/explosion/red.png");
    vector<Explosion> explosions;
    vector<Point> points;
    Helper helper = Helper();

    Player player = Player(Vector2{Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f});

    EnemySpawner enemySpawner = EnemySpawner();
    AsteroidSpawner asteroidSpawner = AsteroidSpawner();
    SoundManager soundManager = SoundManager();

    MainScreen mainScreen = MainScreen();

    Transition transition = Transition(2.f);
    AbilityScreen abilityScreen = AbilityScreen();

    int score = 0;
    float scoreFontSize = 50.f;

    // Shoot rocket timer
    // float spawnRocketTimer = 2.f;

public:
    Camera2D camera = {};

    bool shouldCameraShake = false;
    void SetCameraShake(bool val)
    {
        shouldCameraShake = val;
    };

    Game()
    {
        // HideCursor(); // TODO
        camera.target = Vector2{Settings::WINDOW_WIDTH / 2.0f, Settings::WINDOW_HEIGHT / 2.0f};
        camera.offset = Vector2{Settings::WINDOW_WIDTH / 2.0f, Settings::WINDOW_HEIGHT / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
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
                for (int i = 0; i < points.size(); i++)
                {
                    points[i].Draw();
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

                DrawScore();
            }
            else
            {
                transition.Draw();
            }
        }
        else
        {
            mainScreen.Draw();
            // Draw mouse cursor - cross hair
            Vector2 mousePos = GetMousePosition();
            mousePos.x -= crossHairTexture.width / 2.f;
            mousePos.y -= crossHairTexture.height / 2.f;
            DrawTextureEx(crossHairTexture, mousePos, 0.f, Settings::SCALE, WHITE);
        }
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
            else if (IsKeyPressed(KEY_EIGHT))
            {
                // High Precision fire bullet

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
                        SpawnPoint(e.GetPosition(), enemySpawner.enemies[j].score);
                        soundManager.PlayExplosionSfx();
                        player.UpdateExpBarWidth();
                        IncreaseScore(enemySpawner.enemies[j].score);
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
                SpawnPoint(e.GetPosition(), enemySpawner.enemies[i].score);
                enemySpawner.enemies[i].SetQueueFree(true);
                soundManager.PlayExplosionSfx();
                IncreaseScore(enemySpawner.enemies[i].score);
            }
        }

        // update explosion
        for (int i = 0; i < explosions.size(); i++)
        {
            explosions[i].Update(dt);
        }
        // update points
        for (int i = 0; i < points.size(); i++)
        {
            points[i].Update();
        }

        RemoveExplosion();
        RemovePoints();

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
            particle.speed = {helper.GetRandomFloat(-1, 1), helper.GetRandomFloat(-1, 1)};
            particle.color = explosionColors[ri];
            particle.radius = (float)GetRandomValue(1, 10);
            particle.alpha = 255;
            particle.size = (float)GetRandomValue(1, 20);
            particles.push_back(particle);
        }
    }

    void SpawnPoint(Vector2 position, int val)
    {
        Point point = Point(pixelFont, position, val);
        points.push_back(point);
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

    void RemovePoints()
    {
        for (int i = 0; i < points.size();)
        {
            Point p = points[i];
            if (p.queueFree)
            {
                points.erase(points.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }

    void DrawScore()
    {
        std::string scoreStr = std::to_string(score);
        Vector2 fontSizeVec = MeasureTextEx(pixelFont, scoreStr.c_str(), scoreFontSize, 0.f);
        Vector2 fontPos = {
            Settings::WINDOW_WIDTH / 2.f - fontSizeVec.x / 2.f,
            10.f};
        DrawTextEx(pixelFont, scoreStr.c_str(), fontPos, scoreFontSize, 0.f, WHITE);
    }

    void IncreaseScore(int enemyScore)
    {
        soundManager.PlayPointSfx();
        score += enemyScore;
    }
};

int main()
{
    InitWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, "Edge Of Void");
    InitAudioDevice();

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
            game.camera.target.x += offsetX;
            game.camera.target.y += offsetY;

            shakeDuration -= GetFrameTime();
            game.SetCameraShake(false);
        }
        else
        {
            game.camera.target = Vector2MoveTowards(game.camera.target, Vector2{Settings::WINDOW_WIDTH / 2.0f, Settings::WINDOW_HEIGHT / 2.0f},
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

            BeginMode2D(game.camera);
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