#include "Ponit.h"

Point::Point(Font pf, Vector2 pos, int val)
{
    pixelFont = pf;
    position = pos;
    position.y -= 25;
    position.x -= 20;
    value = val;
}

void Point::Update()
{
    float dt = GetFrameTime();
    fontSize -= dt * 40;
    if (fontSize < 0.f)
    {
        fontSize = 0.f;
        queueFree = true;
    }
    position.y -= dt * 50;
}

void Point::Draw()
{
    std::string intAsString = std::to_string(value);
    const char *charPointer = intAsString.c_str();
    DrawTextEx(pixelFont, charPointer, position, fontSize, 0.f, WHITE);
}