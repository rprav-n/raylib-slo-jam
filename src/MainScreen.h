#pragma once
#include "raylib.h"
#include "Settings.h"
#include <cstdio>

class MainScreen
{

private:
    bool playBtnPressed = false;

    Font pixelFont = LoadFont("./assets/fonts/kenney_pixel.ttf");
    Vector2 dimensions = MeasureTextEx(pixelFont, "Press SPACE to start the game", 20.f, 0.f);
    Vector2 position = Vector2{Settings::WINDOW_WIDTH / 2.f - dimensions.x / 2.f, Settings::WINDOW_HEIGHT / 2.f - dimensions.y / 2.f};

public:
    void Update();
    void Draw();

    bool isPlayPressed()
    {
        return playBtnPressed;
    }
};