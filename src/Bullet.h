#pragma once
#include "raylib.h"
#include "Settings.h"

class Bullet
{
public:
    Bullet(Texture txt, Vector2 pos, Vector2 dir, float rot, int spd);
    bool IsOutOfBounds();
    void Update(float dt);
    void Draw();
    Rectangle GetRect();
    bool IsQueueFree()
    {
        return queueFree;
    };
    void SetQueueFree(bool val)
    {
        queueFree = val;
    };

    Vector2 centerPoint = {};
    float radius = 5.f;

private:
    Texture2D texture;
    Rectangle rect = {};
    Vector2 position = {0.f, 0.f};
    Rectangle dest = {};
    Vector2 origin = {};
    float scaledWidth = 0.f;
    float scaledHeight = 0.f;
    float rotation = 0.f;
    int speed = 800;
    Vector2 direction = {};
    bool queueFree = false;
};
