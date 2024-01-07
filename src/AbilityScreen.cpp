#include "AbilityScreen.h"

void AbilityScreen::Update()
{
}

void AbilityScreen::Draw()
{

    DrawRectangleV({0, 0}, {Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT}, Fade(BLACK, 230.f / 255.0f));

    Vector2 textFontSize = MeasureTextEx(textFont, "Level Up: Hover and Select Your Upgrade!", 26.f, 0.f);
    DrawTextEx(textFont, "Level Up: Hover and Select Your Upgrade!", {Settings::WINDOW_WIDTH / 2.f - textFontSize.x / 2.f, 100.f}, 26.f, 0.f, WHITE);

    current_x = 300.f;
    current_y = 250.f;

    for (size_t i = 0; i < 8; i++)
    {
        UpgradeOption option = upgradeOptions[i];

        Rectangle optionRect = {current_x, current_y, option.texture.width * Settings::SCALE, option.texture.height * Settings::SCALE};

        if (CheckCollisionPointRec(GetMousePosition(), optionRect))
        {
            DrawRectangleRoundedLines(optionRect, 0.5f, 2, 4, Fade(GRAY, 100.f / 255.0f));

            Vector2 optionFontSize = MeasureTextEx(textFont, option.description, 20.f, 0.f);

            DrawTextEx(textFont, option.description, {Settings::WINDOW_WIDTH / 2 - optionFontSize.x / 2.f, 180.f}, 20.f, 0.f, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && upgradeOptions[i].quantity != 0)
            {
                upgradeOptions[i].quantity -= 1;
                pressedNumber = i + 1;
            }
        }
        // else
        // {
        //     pressedNumber = -1;
        // }
        if (upgradeOptions[i].quantity != 0)
        {
            DrawTextureEx(option.texture, {current_x, current_y}, 0.f, Settings::SCALE, WHITE);
        }
        else
        {
            DrawTextureEx(option.texture, {current_x, current_y}, 0.f, Settings::SCALE, RED);
        }

        columnCount++;

        if (columnCount == columns)
        {
            current_x = 300.f;
            current_y += option.texture.height * 3.f + spacing;
            columnCount = 0;
        }
        else
        {
            current_x += option.texture.width * 3.f + spacing;
        }
    }
}