#include "MainScreen.h"

void MainScreen::Update()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        playBtnPressed = true;
    }
}

void MainScreen::Draw()
{
    DrawTextEx(pixelFont, "Press SPACE to start the game", position,
               20.f, 0.f, WHITE);
}