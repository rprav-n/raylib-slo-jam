#include "GameOverScreen.h"

void GameOverScreen::Update()
{
        fontSizeVec = MeasureTextEx(pixelFont, scoreStr.c_str(), scoreFontSize, 0.f);

        scorePos = {
            Settings::WINDOW_WIDTH / 2.f - fontSizeVec.x / 2.f,
            Settings::WINDOW_HEIGHT / 2.5f + 120};
}

void GameOverScreen::Draw()
{
        DrawRectangleV({0, 0}, {Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT},
                       Fade(BLACK, 200.f / 255.0f));

        DrawTextEx(pixelFont, "Game Over",
                   Vector2{Settings::WINDOW_WIDTH / 2.f - titleDimension.x / 2.f,
                           Settings::WINDOW_HEIGHT / 3.f - titleDimension.y / 2.f},
                   72.f, 0.f, WHITE);

        DrawTextEx(pixelFont, yourScoreText.c_str(),
                   Vector2{Settings::WINDOW_WIDTH / 2.f - yourScoreDimension.x / 2.f,
                           Settings::WINDOW_HEIGHT / 2.f - yourScoreDimension.y / 2.f},
                   32.f, 0.f, WHITE);

        DrawTextEx(pixelFont, scoreStr.c_str(), scorePos, scoreFontSize, 0.f, WHITE);
}