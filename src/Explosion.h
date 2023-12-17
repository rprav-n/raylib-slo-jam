#include "raylib.h"
#include "Settings.h"

class Explosion
{
public:
    void Update(float dt, Vector2 pos);
    void Draw();

private:
    Texture2D texture = LoadTexture("./assets/graphics/explosion/red.png");
    const int maxFrame = 3;
    int frame = 0;
    const float updateTime = 1.f / 12.f;
    float runningTime = 0.f;
    float width = texture.width / 3.f;
    float height = (float)texture.height;

    float scaledWidth = width * Settings::SCALE;
    float scaledHeight = height * Settings::SCALE;

    Rectangle source = Rectangle{0.f, 0.f, width, height};
    Rectangle dest = Rectangle{0.f, 0.f, scaledWidth, scaledHeight};

    Vector2 origin = {width / 2.f, height / 2.f};
};
