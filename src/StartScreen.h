#pragma once
#include "raylib.h"
#include "Settings.h"
#include "Button.h"
#include <cstdio>

class StartScreen
{

private:
    Font pixelFont = LoadFont("./assets/fonts/score.ttf");

    Texture2D playBtnTexture = LoadTexture("./assets/graphics/ui/play_btn2.png");
    Texture2D closeBtnTexture = LoadTexture("./assets/graphics/ui/close_btn.png");

    Vector2 titleDimension = MeasureTextEx(pixelFont, "Edge Of Void", 64.f, 0.f);

    Button playBtn = Button(playBtnTexture, {Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f});
    Button closeBtn = Button(closeBtnTexture, {Settings::WINDOW_WIDTH / 2.f, Settings::WINDOW_HEIGHT / 2.f + 70.f});

public:
    void Update();
    void Draw();
    bool IsPlayBtnPressed()
    {
        return playBtn.btnAction;
    }
    bool IsCloseBtnPressed()
    {
        return closeBtn.btnAction;
    }
};