#pragma once
#include "raylib.h"

class SoundManager
{
private:
    Sound explosionSfx = LoadSound("./assets/sounds/explosion.wav");
    Music bgMusic = LoadMusicStream("./assets/music/bg.ogg");

public:
    SoundManager()
    {
        SetMusicVolume(bgMusic, 0.1f);
        // PlayMusicStream(bgMusic); // TODO uncomment
    };

    void UpdateMusic(){
        // UpdateMusicStream(bgMusic); // TODO uncomment
    };

    void PlayExplosionSfx()
    {
        PlaySound(explosionSfx);
    };
};