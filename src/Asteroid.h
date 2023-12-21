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

public:
    Asteroid(Texture2D txtr, Vector2 pos, Vector2 dir);
    void Update();
    void Draw();
};