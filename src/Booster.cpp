#include "Booster.h"

Booster::Booster()
{
    scaledWidth = width * Settings::SCALE;
    scaledHeight = height * Settings::SCALE;

    origin = {scaledWidth / 2.f,
              scaledHeight / 2.f - 6.f * Settings::SCALE};
}

void Booster::Update(double dt, Vector2 pos, float rot)
{
    rotation = rot;
    dest.x = pos.x;
    dest.y = pos.y;

    runningTime += dt;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }
}

void Booster::Draw()
{
    source.x = frame * width;
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}