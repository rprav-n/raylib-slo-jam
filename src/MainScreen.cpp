#include "MainScreen.h"

void MainScreen::Update()
{
    mousePoint = GetMousePosition();
    btnAction = false;
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else
        btnState = 0;

    source.x = width * btnState;
}

void MainScreen::Draw()
{

    DrawTextEx(pixelFont, "Edge Of Void", Vector2{Settings::WINDOW_WIDTH / 2.f - titleDimension.x / 2.f, Settings::WINDOW_HEIGHT / 3.f - titleDimension.y / 2.f}, 64.f, 0.f, WHITE);
    DrawTexturePro(playBtnTexture, source, dest, origin, 0.f, WHITE);
}