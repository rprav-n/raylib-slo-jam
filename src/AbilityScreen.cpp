#include "AbilityScreen.h"

void AbilityScreen::Update()
{
}

void AbilityScreen::Draw()
{
    DrawText("Upgrade Your Ship", 100.f, 100.f, 24.f, WHITE);
    DrawText("1 - Auto Shoot", 100.f, 150.f, 24.f, WHITE);
    DrawText("2 - Double Bullet", 100.f, 200.f, 24.f, WHITE);
    DrawText("3 - Dashing", 100.f, 250.f, 24.f, WHITE);
    DrawText("4 - Increase Auto Shoot Speed by 10%", 100.f, 300.f, 24.f, WHITE);
    DrawText("5 - Full Health", 100.f, 350.f, 24.f, WHITE);
    DrawText("6 - Get Shield or Full Sheild", 100.f, 400.f, 24.f, WHITE);
    DrawText("7 - Shoot 3 Burst Bullets", 100.f, 450.f, 24.f, WHITE);
}