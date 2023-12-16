#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet(Texture txt, Vector2 pos, Vector2 dir, float rot)
{
    texture = txt;
    rect = Rectangle{0.f, 0.f, (float)texture.width, (float)texture.height};
    dest = Rectangle{0.f, 0.f, texture.width * Settings::SCALE, texture.height * Settings::SCALE};
    origin = {texture.width * Settings::SCALE / 2.f, texture.height * Settings::SCALE / 2.f};
    position = pos;
    direction = dir;
    rotation = rot;
}

bool Bullet::IsOutOfBounds()
{
    if (position.y < 0 || position.y > Settings::WINDOW_HEIGHT + Settings::BULLET_OFFSET_BOUND ||
        position.x < -Settings::BULLET_OFFSET_BOUND || position.x > Settings::WINDOW_WIDTH + Settings::BULLET_OFFSET_BOUND)
    {
        return true;
    }
    return false;
}

void Bullet::Update(float dt)
{
    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;

    dest.x = position.x;
    dest.y = position.y;
}

void Bullet::Draw()
{
    // DrawTextureEx(texture, position, 0.f, SCALE, WHITE);
    DrawTexturePro(texture, rect, dest, origin, rotation, WHITE);
}