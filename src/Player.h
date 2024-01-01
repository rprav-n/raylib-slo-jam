#pragma once
#include "raylib.h"
#include "Bullet.h"
#include "Booster.h"
#include "Settings.h"
#include "Helper.h"
#include <vector>
#include <cstdio>

using namespace std;

class Player
{

public:
    Player(Vector2 pos);
    Helper helper = Helper();
    Vector2 GetMovementDirection();

    void Update(double dt);
    void Draw();
    void CheckCollisionBounds();
    void ShootBullet();

    Vector2 GetPosition();
    Vector2 GetTopLeftPosition()
    {
        return topLeftOrigin;
    };
    Vector2 GetSize()
    {
        return Vector2{scaledWidth, scaledHeight};
    };
    float GetRotation();
    Vector2 GetVectorRotation();

    vector<Bullet> bullets;

    Vector2 centerPoint = {};
    float SHIP_RADIUS = 12.f;
    float SHIELD_RADIUS = 32.f;
    float radius = 12.f;
    bool showAbilityScreen = true;

    void PlayLaserSfx();
    void ReduceHealth();
    void UpdateExpBarWidth();
    void GetFullHealth();
    void GetFullShield();
    void KnockBack();

    // bullet speed
    int bulletSpeed = 800;

    // Auto Shoot
    bool canAutoShoot = false;
    float shootSpanwnTimer = 0.3f;
    float shootTimer = 0.0f;

    // Double gun
    bool hasDoubleGun = false;
    Vector2 leftGunPosition = {};
    Vector2 rightGunPosition = {};

    // Player speed variables
    float acceleration = 10.f;
    float speed = 5.f;

    // Dashing
    bool isDashing = false;
    bool hasDash = false;
    int dashParticlesCount = 50;
    Particle dashingParticles[50];
    void UpdateDashingParticles();
    void DrawDashingParticles();
    float maxDashDuration = 0.4f;
    float currentDashDuration = 0.0f;
    float dashCooldown = 2.f;
    float timeSinceLastDash = 0.f;

    // Shield
    bool hasShied = false;

    // Shoot rockets every 2sec and hit the nearby enemy
    bool shootRockets = false;

    // Bomb - spanwn bomb every 5 sec
    bool deployBomb = true;

    // Burst bullets
    bool hasBurstBullet = false;
    int burstCount = 1; // 1 is 1,1,1 | 2 - 1, 1,1, 1 and son on

    // High precision
    bool hasHighPrecisionBullet = false;

    float GetRadius()
    {
        return radius;
    };

    bool isDead = false;

private:
    Texture2D texture = LoadTexture("./assets/graphics/ships/green_ship.png");
    Texture2D red_bullet = LoadTexture("./assets/graphics/bullets/red_bullet.png");
    Texture2D boosterTexture = LoadTexture("./assets/graphics/booster/medium.png");
    Texture2D healthProgressTexture = LoadTexture("./assets/graphics/ui/health_ui.png");
    Texture2D heartIconTexture = LoadTexture("./assets/graphics/ui/heart_icon.png");
    Texture2D shieldIconTexture = LoadTexture("./assets/graphics/ui/shield_icon.png");
    Texture2D shieldTexture = LoadTexture("./assets/graphics/shield/shield_sheet.png");
    Texture2D bombTexture = LoadTexture("./assets/graphics/ships/bomb.png");

    Sound laserSfx = LoadSound("./assets/sounds/laser_shoot.wav");

    Vector2 direction = {};
    Vector2 velocity = {0.0f, 0.0f};
    float rotation = 0.f;
    float rotationSpeed = 200.0f;

    float width = 0.f;
    float height = 0.f;

    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Rectangle source = Rectangle{texture.width / 3.f, 0.f, texture.width / 3.f, (float)texture.height};
    Vector2 position = {0.f, 0.f};
    Rectangle dest = Rectangle{position.x, position.y, source.width *Settings::SCALE, (float)source.height *Settings::SCALE};
    Vector2 centerOrigin = {};
    Vector2 topLeftOrigin = {};
    Vector2 boosterPos = {};
    Vector2 origin = {};
    Booster booster = Booster(boosterTexture, Vector2{0.f, 0.f});

    // Health
    float MAX_HEALTH = 150.f;
    Vector2 healthBarPos = {30.f, 10.f};
    Vector2 healthBarSize = {MAX_HEALTH, 16.f};
    Rectangle healthBarBorderRect = {healthBarPos.x, healthBarPos.y, healthBarSize.x, 16.f};

    // Shield bar
    float MAX_SHIELD = 150.f;
    Vector2 shieldBarPos = {30.f, 30.f};
    Vector2 shieldBarSize = {MAX_SHIELD, 16.f};
    Rectangle shieldBarBorderRect = {shieldBarPos.x, shieldBarPos.y, shieldBarSize.x, 16.f};

    // Shield
    int frame = 3;
    float shieldWidth = shieldTexture.width / 4.f;
    float shieldHeight = (float)shieldTexture.height;

    float scaledShieldWidth = shieldWidth * Settings::SCALE;
    float scaledShieldHeight = shieldHeight * Settings::SCALE;

    Rectangle shieldSource = Rectangle{frame * shieldWidth, 0.f, shieldWidth, shieldHeight};
    Rectangle shieldDest = Rectangle{0.f, 0.f, scaledShieldWidth, scaledShieldHeight};
    Vector2 shieldCenterOrigin = {scaledShieldWidth / 2.f, scaledShieldHeight / 2.f};

    // Expirence
    int level = 0;
    float expIncreaseBy = 250.f;

    float MAX_EXP_BAR = Settings::WINDOW_WIDTH - 100.f;
    Vector2 experienceBarPos = {50.f, Settings::WINDOW_HEIGHT - 30.f};
    Vector2 experienceBarSize = {0.f, 16.f};
    Rectangle experienceBarBorderRect = {experienceBarPos.x, experienceBarPos.y, MAX_EXP_BAR, 16.f};

    // Colors
    Color pink = GetColor(0xdb41c3ff);
    Color green = GetColor(0x71e392ff);
    Color lightBlue = GetColor(0x61d3e3ff);
};