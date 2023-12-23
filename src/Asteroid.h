#pragma once
#include "raylib.h"
#include "Settings.h"
#include <cstdio>

class Asteroid
{
private:
    Texture2D texture = {};
    Vector2 position = {};
    float scaledWidth = 0.f;
    float scaledHeight = 0.f;
    Vector2 origin = {};
    Rectangle source = {};
    Rectangle dest = {};
    Vector2 direction = {};

    float rotation = 0.f;
    float speed = 100.f;
    float rotSpeed = 1.f;
    int type = 0; // 0 - small, 1 - big
    bool queueFree = false;

public:
    Asteroid(Texture2D txtr, Vector2 pos, Vector2 dir, int t);
    void Update();
    void Draw();
    void SetQueueFree(bool val)
    {
        queueFree = val;
    }

    bool IsQueueFree() const
    {
        return queueFree;
    };

    float GetYPos()
    {
        return dest.y;
    }
};