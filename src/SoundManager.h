#pragma once
#include "raylib.h"

class SoundManager
{
private:
    Sound explosionSfx = LoadSound("./assets/sounds/explosion.wav");

public:
    void PlayExplosionSfx()
    {
        PlaySound(explosionSfx);
    };
};