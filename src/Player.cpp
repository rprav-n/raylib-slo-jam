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

    Vector2 direction = GetMovementDirection(); // normalized direction vector
    if (IsKeyPressed(KEY_SPACE))
    {
        ShootBullet();
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
    velocity = Vector2MoveTowards(velocity, targetVelocity, acceleration * dt);
    position = Vector2Add(position, velocity);

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update(dt);
    }

    // Remove bullet if it goes beyound the screen
    for (int i = 0; i < bullets.size();)
    {
        Bullet b = bullets[i];
        if (b.IsOutOfBounds())
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

    dest.x = position.x;
    dest.y = position.y;

    boosterPos = {position.x, position.y + scaledHeight / 2.f};

    booster.Update(dt, position, rotation);
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
}

void Player::Draw()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
    booster.Draw();
}

void Player::ShootBullet()
{
    Vector2 bulletDirection = Vector2Rotate({0, -1}, DEG2RAD * rotation);
    Bullet bullet = Bullet(red_bullet, centerOrigin, bulletDirection, rotation);
    bullets.push_back(bullet);
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
    ;
}