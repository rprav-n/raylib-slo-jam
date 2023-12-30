#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet(Texture txt, Vector2 pos, Vector2 dir, float rot, int spd, Color colr)
{
    texture = txt;
    scaledWidth = txt.width * Settings::SCALE;
    scaledHeight = txt.height * Settings::SCALE;
    rect = Rectangle{0.f, 0.f, (float)texture.width, (float)texture.height};
    dest = Rectangle{0.f, 0.f, texture.width * Settings::SCALE, texture.height * Settings::SCALE};

    origin = {scaledWidth / 2.f, scaledHeight / 2.f};
    position = pos;
    direction = dir;
    rotation = rot;
    speed = spd;

    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        trailParticles[i].position = position;
        trailParticles[i].color = colr;
        trailParticles[i].alpha = 255.f;
    }
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

    centerPoint = position;
    UpdateTrailParticles();
}

void Bullet::Draw()
{
    DrawTrailParticles();
    DrawTexturePro(texture, rect, dest, origin, rotation, WHITE);
}

Rectangle Bullet::GetRect()
{
    return dest;
}

void Bullet::UpdateTrailParticles()
{
    for (int i = MAX_PARTICLES - 1; i > 0; --i)
    {
        trailParticles[i].position = trailParticles[i - 1].position;
        trailParticles[i].alpha = trailParticles[i - 1].alpha;
    }

    trailParticles[0].position = position;
    trailParticles[0].alpha = 255.0f;

    // Update particles
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        trailParticles[i].alpha -= 20.0f;
        if (trailParticles[i].alpha <= 0)
        {
            trailParticles[i].alpha = 0;
        }
    }
}

void Bullet::DrawTrailParticles()
{
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        DrawRectangleV(trailParticles[i].position, {3.f, 3.f},
                       Fade(trailParticles[i].color, trailParticles[i].alpha / 255.0f));
    }
}