#include "raylib.h"
#include "Settings.h"

class PauseScreen
{
public:
    void Update();
    void Draw();

private:
    Font pixelFont = LoadFont("./assets/fonts/kenney_pixel.ttf");

    Vector2 titleDimension = MeasureTextEx(pixelFont, "PAUSED", 64.f, 0.f);
};