#include "StartScreen.h"

void StartScreen::Update()
{
    float dt = GetFrameTime();
    playBtn.Update();
    closeBtn.Update();

    yPos += speed * dt;
    if (yPos > 205.f || yPos < 195) {
        speed *= -1;
    }
}

void StartScreen::Draw()
{

    DrawTextEx(pixelFont, "Edge Of Void", Vector2{Settings::WINDOW_WIDTH / 2.f - titleDimension.x / 2.f, yPos}, 64.f, 0.f, WHITE);
    playBtn.Draw();
    closeBtn.Draw();
}