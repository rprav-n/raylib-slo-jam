#include "raylib.h"
#include <iostream>

class Point
{
public:
    float spawnTime = 2.f;
    float currentTimer = 0.f;
    Vector2 position;
    Font pixelFont;
    bool queueFree = false;
    float fontSize = 48.f;
    int value = 25;

    Point(Font pf, Vector2 pos, int p);
    void Update();
    void Draw();
};