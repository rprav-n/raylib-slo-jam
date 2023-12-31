#include "Button.h"

Button::Button(Texture2D txtr, Vector2 pos)
{
    texture = txtr;

    width = texture.width / 3.f;
    height = texture.height;

    source = Rectangle{0.f, 0.f, width, height};
    position = pos;
    dest = {position.x, position.y, source.width * Settings::SCALE, source.height * Settings::SCALE};
    origin = {dest.width / 2.f, dest.height / 2.f};

    btnBounds = {position.x - dest.width / 2.f, position.y - dest.height / 2.f, dest.width, dest.height};
}

void Button::Update()
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

void Button::Draw()
{
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}