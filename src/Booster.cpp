#include "Booster.h"
#include "raymath.h"
#include <cstdio>

Booster::Booster(Texture2D txtr, Vector2 originOffset)
{
    texture = txtr;

    width = texture.width / (float)maxFrame;
    height = (float)texture.height;
    scaledWidth = width * Settings::SCALE;
    scaledHeight = height * Settings::SCALE;

    origin = {scaledWidth / 2.f,
              0.f};
    origin = Vector2Add(origin, originOffset);

    printf("texture.width %d\n", texture.width);

    source = Rectangle{0.f, 0.f, texture.width / (float)maxFrame, (float)texture.height};
    dest = Rectangle{100.f, 100.f, width * Settings::SCALE, height * Settings::SCALE};
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