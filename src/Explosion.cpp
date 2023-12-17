#include "Explosion.h"

Explosion::Explosion(Texture txtr, Vector2 pos)
{
    texture = txtr;

    width = texture.width / 3.f;
    height = (float)texture.height;

    scaledWidth = width * Settings::SCALE;
    scaledHeight = height * Settings::SCALE;

    source = Rectangle{0.f, 0.f, width, height};
    dest = Rectangle{0.f, 0.f, scaledWidth, scaledHeight};

    origin = {scaledWidth / 2.f, scaledHeight / 2.f};

    dest.x = pos.x;
    dest.y = pos.y;
}

void Explosion::Update(float dt)
{
    runningTime += dt;
    if (runningTime >= updateTime && !queueFree)
    {
        runningTime = 0.f;
        frame++;

        if (frame >= maxFrame)
        {
            frame = 0;
            queueFree = true;
        }
    }
}

void Explosion::Draw()
{
    source.x = frame * width;
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}
