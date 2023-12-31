#include "StartScreen.h"

void StartScreen::Update()
{
    playBtn.Update();
    closeBtn.Update();
}

void StartScreen::Draw()
{

    DrawTextEx(pixelFont, "Edge Of Void", Vector2{Settings::WINDOW_WIDTH / 2.f - titleDimension.x / 2.f, Settings::WINDOW_HEIGHT / 3.f - titleDimension.y / 2.f}, 64.f, 0.f, WHITE);
    playBtn.Draw();
    closeBtn.Draw();
}