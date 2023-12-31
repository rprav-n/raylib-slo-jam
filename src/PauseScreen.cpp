#include "PauseScreen.h"

void PauseScreen::Update()
{
}

void PauseScreen::Draw()
{

    DrawRectangleV({0, 0}, {Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT},
                   Fade(BLACK, 200.f / 255.0f));
    DrawTextEx(pixelFont, "PAUSED",
               Vector2{Settings::WINDOW_WIDTH / 2.f - titleDimension.x / 2.f,
                       Settings::WINDOW_HEIGHT / 3.f - titleDimension.y / 2.f},
               64.f, 0.f, WHITE);
}