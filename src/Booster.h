#include "raylib.h"
#include "Settings.h"

class Booster
{

public:
    Booster();
    void Update(double dt, Vector2 pos, float rot);
    void Draw();

private:
    Texture2D texture = LoadTexture("./assets/graphics/booster/small/sheet.png");
    int frame = 0;
    const int maxFrame = 4;
    float width = texture.width / maxFrame;
    float height = (float)texture.height;
    Rectangle source = Rectangle{0.f, 0.f, texture.width / 4.f, (float)texture.height};
    Rectangle dest = Rectangle{100.f, 100.f, width *Settings::SCALE, height *Settings::SCALE};
    Vector2 origin = {};
    float updateTime = 1.f / 16.f;
    float runningTime = 0.f;
    float rotation = 0.f;
    float scaledWidth = 0.f;
    float scaledHeight = 0.f;
};