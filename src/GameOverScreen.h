#pragma once
#include "raylib.h"
#include "Settings.h"
#include "Helper.h"
#include <string>

class GameOverScreen
{
public:
    void Update();
    void Draw();

    void UpdateScore(int val)
    {
        score = val;
        scoreStr = std::to_string(score);
    };

    int score = 123;
    int scoreFontSize = 60;

    std::string scoreStr = std::to_string(score);
    std::string yourScoreText = "Your Score:";

private:
    Font pixelFont = LoadFont("./assets/fonts/score.ttf");

    Vector2 titleDimension = MeasureTextEx(pixelFont, "Game Over", 72.f, 0.f);
    Vector2 yourScoreDimension = MeasureTextEx(pixelFont, "Your Score", 32.f, 0.f);

    Vector2 fontSizeVec = MeasureTextEx(pixelFont, scoreStr.c_str(), scoreFontSize, 0.f);
    Vector2 scorePos = {
        Settings::WINDOW_WIDTH / 2.f - fontSizeVec.x / 2.f,
        Settings::WINDOW_HEIGHT / 2.f + 10};
};
