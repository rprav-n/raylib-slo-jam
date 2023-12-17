#include "Explosion.h"

void Explosion::Update(float dt, Vector2 pos)
{
    runningTime += dt;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;

        if (frame >= maxFrame)
        {
            frame = 0;
        }
    }
    dest.x = pos.x;
    dest.y = pos.y;
}

void Explosion::Draw()
{
    source.x = frame * width;
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}
