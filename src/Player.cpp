#include "Player.h"
#include "raylib.h"
#include "raymath.h"

Player::Player(Vector2 pos)
{
    position = pos;
    width = texture.width / 3.f;
    height = texture.height;

    scaledWidth = width * Settings::SCALE;
    scaledHeight = height * Settings::SCALE;

    origin = {scaledWidth / 2.f,
              scaledHeight / 2.f};
}

Vector2 Player::GetMovementDirection()
{
    Vector2 movement_direction = {};
    // if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    //     movement_direction.x = -1;
    // if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    //     movement_direction.x = 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        movement_direction.y = -1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        movement_direction.y = 1;

    return Vector2Normalize(movement_direction);
}

void Player::Update(double dt)
{
    if (hasShied)
    {
        radius = SHIELD_RADIUS;
    }
    else
    {
        radius = SHIP_RADIUS;
    }
    direction = GetMovementDirection(); // normalized direction vector
    if (IsKeyPressed(KEY_SPACE) && !canAutoShoot)
    {
        PlayLaserSfx();
        ShootBullet();
    }

    if (canAutoShoot)
    {
        shootTimer += dt;
        if (shootTimer >= shootSpanwnTimer)
        {
            shootTimer = 0.f;
            PlayLaserSfx();
            ShootBullet();
        }
    }

    if (IsKeyPressed(KEY_LEFT_SHIFT) && hasDash)
    {
        isDashing = true;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        rotation -= rotationSpeed * dt;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        rotation += rotationSpeed * dt;
    }

    // rotation = Clamp(rotation, -360.0f, 360.0f);
    if (rotation < -360.f || rotation > 360.f)
    {
        rotation = 0.f;
    }

    Vector2 rotatedDirection = Vector2Rotate(direction, DEG2RAD * rotation);

    Vector2 targetVelocity = {rotatedDirection.x * speed, rotatedDirection.y * speed};

    // Shift to dash
    if (isDashing)
    {
        // TODO
        // Implement dash shaders
        velocity = {};
        targetVelocity = Vector2Scale(targetVelocity, 100);
        velocity = Vector2MoveTowards(velocity, targetVelocity, 50 * acceleration * dt);
        isDashing = false;
    }
    else
    {
        velocity = Vector2MoveTowards(velocity, targetVelocity, acceleration * dt);
    }

    position = Vector2Add(position, velocity);

    // Rotate the player based on Mouse Position
    // Vector2 direction = Vector2Subtract(GetMousePosition(), position);
    // rotation = atan2f(direction.y, direction.x) * RAD2DEG + 90.f;
    // if (rotation < -360.f || rotation > 360.f)
    // {
    //     rotation = 0.f;
    // }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update(dt);
    }

    // Remove bullet if it goes beyound the screen
    for (int i = 0; i < bullets.size();)
    {
        Bullet b = bullets[i];
        if (b.IsOutOfBounds() || b.IsQueueFree())
        {
            bullets.erase(bullets.begin() + i);
        }
        else
        {
            ++i;
        }
    }

    CheckCollisionBounds();

    topLeftOrigin.x = position.x - scaledWidth / 2.f;
    topLeftOrigin.y = position.y - scaledHeight / 2.f;

    centerOrigin.x = topLeftOrigin.x + scaledWidth / 2.f;
    centerOrigin.y = topLeftOrigin.y + scaledHeight / 2.f;

    leftGunPosition.x = position.x - 10.f;
    leftGunPosition.y = position.y;

    rightGunPosition.x = position.x + 10.f;
    rightGunPosition.y = position.y;

    dest.x = position.x;
    dest.y = position.y;

    shieldDest.x = centerOrigin.x;
    shieldDest.y = centerOrigin.y;

    boosterPos = {position.x, position.y + scaledHeight / 2.f};

    booster.Update(dt, position, rotation);

    centerPoint = position;
}

void Player::CheckCollisionBounds()
{
    if (position.x <= scaledWidth / 2.f)
    {
        position.x = 0 + scaledWidth / 2.f;
    }
    if (position.x + scaledWidth / 2.f >= Settings::WINDOW_WIDTH)
    {
        position.x = Settings::WINDOW_WIDTH - scaledWidth / 2.f;
    }

    if (position.y <= scaledHeight / 2.f)
    {
        position.y = 0 + scaledHeight / 2.f;
    }
    if (position.y + scaledHeight / 2.f >= Settings::WINDOW_HEIGHT)
    {
        position.y = Settings::WINDOW_HEIGHT - scaledHeight / 2.f;
    }
}

void Player::Draw()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
    booster.Draw();

    // heart and shield icons
    DrawTextureEx(heartIconTexture, Vector2{5, 10}, 0.f, 0.8, WHITE);
    if (hasShied)
    {
        DrawTextureEx(shieldIconTexture, Vector2{5, 30}, 0.f, 0.8, WHITE);
    }

    // health bar
    DrawRectangleV(healthBarPos, healthBarSize, pink);
    DrawRectangleLinesEx(healthBarBorderRect, 4.f, WHITE);

    // shield bar
    if (hasShied)
    {
        DrawRectangleV(shieldBarPos, shieldBarSize, lightBlue);
        DrawRectangleLinesEx(shieldBarBorderRect, 4.f, WHITE);
    }

    // expirence bar
    DrawRectangleV(experienceBarPos, experienceBarSize, green);
    DrawRectangleLinesEx(experienceBarBorderRect, 4.f, WHITE);

    // player shield
    if (hasShied)
    {
        DrawTexturePro(shieldTexture, shieldSource, shieldDest, shieldCenterOrigin, 0.f, WHITE);
    }

    Vector2 relativeLeftPosition = Vector2Subtract(leftGunPosition, position);
    Vector2 rotatedRelativeLeftPosition = Vector2Rotate(relativeLeftPosition, rotation * DEG2RAD);
    leftGunPosition = Vector2Add(position, rotatedRelativeLeftPosition);

    Vector2 relativeRightPosition = Vector2Subtract(rightGunPosition, position);
    Vector2 rotatedRelativeRightPosition = Vector2Rotate(relativeRightPosition, rotation * DEG2RAD);
    rightGunPosition = Vector2Add(position, rotatedRelativeRightPosition);

    // debug: drawing left, right gun position
    // DrawCircleV(leftGunPosition, 5.f, RED);
    // DrawCircleV(rightGunPosition, 5.f, BLUE);
    // DrawCircleV(centerPoint, SHIELD_RADIUS, RED);

    // TODO Flicker Shield with WHITE Color when get hit
    if (hasShied)
    {
    }
}

void Player::ShootBullet()
{
    if (hasDoubleGun)
    {

        Vector2 leftBulletDirection = Vector2Rotate({0, -1}, DEG2RAD * rotation);
        Bullet leftBullet = Bullet(red_bullet, leftGunPosition, leftBulletDirection, rotation, bulletSpeed);

        Vector2 rightBulletDirection = Vector2Rotate({0, -1}, DEG2RAD * rotation);
        Bullet rightBullet = Bullet(red_bullet, rightGunPosition, rightBulletDirection, rotation, bulletSpeed);

        bullets.push_back(leftBullet);
        bullets.push_back(rightBullet);
    }
    else if (hasBurstBullet)
    {

        for (int i = -burstCount; i <= burstCount; i++)
        {
            Vector2 bulletDirection = Vector2Rotate({i * 0.1f, -1}, DEG2RAD * rotation);
            Bullet bullet = Bullet(red_bullet, centerOrigin, bulletDirection, rotation, bulletSpeed);
            bullets.push_back(bullet);
        }
    }
    else
    {
        Vector2 bulletDirection = Vector2Rotate({0, -1}, DEG2RAD * rotation);
        Bullet bullet = Bullet(red_bullet, centerOrigin, bulletDirection, rotation, bulletSpeed);
        bullets.push_back(bullet);
    }
}

Vector2 Player::GetPosition()
{
    return position;
}

float Player::GetRotation()
{
    return rotation;
}

Vector2 Player::GetVectorRotation()
{
    Vector2 direction = GetMovementDirection();
    return Vector2Rotate(direction, DEG2RAD * rotation);
}

void Player::PlayLaserSfx()
{
    PlaySound(laserSfx);
};

void Player::ReduceHealth()
{

    if (hasShied)
    {
        shieldBarSize.x -= 10.f;
        if (shieldBarSize.x <= 0.f)
        {
            hasShied = false;
            // TODO play shield loss sound
        }
    }
    else
    {
        healthBarSize.x -= 10.f;
        if (healthBarSize.x <= 0.f)
        {
            // TODO destroy player, game over
        }
        else
        {
        }
    }
}

void Player::UpdateExpBarWidth()
{
    experienceBarSize.x += expIncreaseBy;

    if (experienceBarSize.x >= MAX_EXP_BAR)
    {
        experienceBarSize.x = 0;
        // TODO reduce expirence by 10% of previous
        float reducedValue = expIncreaseBy * 0.1;
        expIncreaseBy -= reducedValue;
        printf("expIncreaseBy %f\n", expIncreaseBy);
        if (expIncreaseBy < 30.f)
        {
            expIncreaseBy = 30.f;
        }
        level++;
        showAbilityScreen = true;
    }
}

void Player::GetFullHealth()
{
    healthBarSize.x = MAX_HEALTH;
}
void Player::GetFullShield()
{
    shieldBarSize.x = MAX_SHIELD;
}