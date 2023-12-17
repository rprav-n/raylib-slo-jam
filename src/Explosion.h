#pragma once
#include "raylib.h"
#include "Settings.h"

class Explosion
{
public:
    Explosion(Texture2D txtr, Vector2 pos);
    void Update(float dt);
    void Draw();

    bool IsQueueFree()
    {
        return queueFree;
    }

private:
    Texture2D texture;
    int maxFrame = 3;
    int frame = 0;
    float updateTime = 1.f / 12.f;
    float runningTime = 0.f;
    float width = 0.f;
    float height = 0.f;

    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Rectangle source = {};
    Rectangle dest = {};

    Vector2 origin = {};

    bool queueFree = false;
};
