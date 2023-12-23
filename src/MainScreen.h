#pragma once
#include "raylib.h"
#include "Settings.h"
#include <cstdio>

class MainScreen
{

private:
    Texture2D playBtnTexture = LoadTexture("./assets/graphics/ui/play_btn.png");
    float width = playBtnTexture.width / 3.f;
    float height = playBtnTexture.height;

    Rectangle source = Rectangle{0.f, 0.f, width, height};
    Vector2 position = Vector2{Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f};
    Rectangle dest = {position.x, position.y, source.width *Settings::SCALE, source.height *Settings::SCALE};
    Vector2 origin = {dest.width / 2.f, dest.height / 2.f};

    Rectangle btnBounds = {position.x - dest.width / 2.f, position.y - dest.height / 2.f, dest.width, dest.height};

    int btnState = 0; // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;
    Vector2 mousePoint = {0.0f, 0.0f};

public:
    void Update();
    void Draw();
};