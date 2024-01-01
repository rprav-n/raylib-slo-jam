#include "AbilityScreen.h"

void AbilityScreen::Update()
{
}

void AbilityScreen::Draw()
{

    DrawRectangleV({0, 0}, {Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT}, Fade(BLACK, 200.f / 255.0f));

    // DrawText("Upgrade Your Ship", 100.f, 100.f, 24.f, WHITE);
    // DrawText("1 - Auto Shoot", 100.f, 150.f, 24.f, WHITE);
    // DrawText("2 - Double Bullet", 100.f, 200.f, 24.f, WHITE);
    // DrawText("3 - Dashing", 100.f, 250.f, 24.f, WHITE);
    // DrawText("4 - Increase Auto Shoot Speed by 10%", 100.f, 300.f, 24.f, WHITE);
    // DrawText("5 - Full Health", 100.f, 350.f, 24.f, WHITE);
    // DrawText("6 - Get Shield or Full Sheild", 100.f, 400.f, 24.f, WHITE);
    // DrawText("7 - Shoot 3 Burst Bullets", 100.f, 450.f, 24.f, WHITE);
    // DrawText("8 - Hight Bullet Precision", 100.f, 500.f, 24.f, WHITE);

    current_x = 310.f;
    current_y = 200.f;

    DrawText("Upgrade Your Ship", 100.f, 100.f, 24.f, WHITE);

    for (const auto &option : upgradeOptions)
    {

        Rectangle optionRect = {current_x, current_y, option.texture.width * Settings::SCALE, option.texture.height * Settings::SCALE};

        if (CheckCollisionPointRec(GetMousePosition(), optionRect))
        {
            DrawRectangleRoundedLines(optionRect, 0.1f, 2, 4, WHITE);
        }

        DrawTextureEx(option.texture, {current_x, current_y}, 0.f, Settings::SCALE, WHITE);
        columnCount++;

        if (columnCount == columns)
        {
            current_x = 310.f;
            current_y += option.texture.height * 3.f + spacing;
            columnCount = 0;
        }
        else
        {
            current_x += option.texture.width * 3.f + spacing;
        }
    }
}