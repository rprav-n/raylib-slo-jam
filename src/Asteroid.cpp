#include "Asteroid.h"
#include "raymath.h"

Asteroid::Asteroid(Texture2D txtr, Vector2 pos, Vector2 dir)
{
    texture = txtr;
    position = pos;
    scaledWidth = texture.width * Settings::SCALE;
    scaledHeight = texture.height * Settings::SCALE;
    origin = {scaledWidth / 2.f, scaledHeight / 2.f};
    source = Rectangle{0.f, 0.f, (float)texture.width, (float)texture.height};
    dest = Rectangle{0.f, 0.f, scaledWidth, scaledHeight};
    direction = dir;
}

void Asteroid::Update()
{
    double dt = GetFrameTime();

    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;

    dest.x = position.x;
    dest.y = position.y;

    rotation += 1;
    if (rotation >= 360)
    {
        rotation = 0;
    }
}

void Asteroid::Draw()
{
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}