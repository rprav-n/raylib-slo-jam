#pragma once
#include "raylib.h"
#include "Settings.h"

class Booster
{

public:
    Booster(Texture2D txtr, Vector2 originOffset);
    void Update(double dt, Vector2 pos, float rot);
    void Draw();

private:
    Texture2D texture = LoadTexture("./assets/graphics/booster/medium.png");
    int frame = 0;
    const int maxFrame = 4;
    float width = 0.f;
    float height = 0.f;
    Rectangle source = {};
    Rectangle dest = {};
    Vector2 origin = {};
    float updateTime = 1.f / 16.f;
    float runningTime = 0.f;
    float rotation = 0.f;
    float scaledWidth = 0.f;
    float scaledHeight = 0.f;
};