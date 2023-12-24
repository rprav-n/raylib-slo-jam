#include "AbilityScreen.h"

void AbilityScreen::Update()
{
}

void AbilityScreen::Draw()
{
    DrawText("Upgrade Your Ship", 100.f, 100.f, 24.f, WHITE);
    DrawText("1 - Auto Shoot", 100.f, 150.f, 24.f, WHITE);
    DrawText("2 - Double Bullet", 100.f, 200.f, 24.f, WHITE);
}