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
    DrawTexturePro(playBtnTexture, source, dest, origin, 0.f, WHITE);
}