#include "raylib.h"
#include "Settings.h"
#include <vector>

using namespace std;

struct UpgradeOption
{
    Texture2D texture;
    const char *description;
    int quantity;
};

class AbilityScreen
{
private:
    // DrawText("Upgrade Your Ship", 100.f, 100.f, 24.f, WHITE);
    // DrawText("1 - Auto Shoot", 100.f, 150.f, 24.f, WHITE);
    // DrawText("2 - Double Bullet", 100.f, 200.f, 24.f, WHITE);
    // DrawText("3 - Dashing", 100.f, 250.f, 24.f, WHITE);
    // DrawText("4 - Increase Auto Shoot Speed by 10%", 100.f, 300.f, 24.f, WHITE);
    // DrawText("5 - Full Health", 100.f, 350.f, 24.f, WHITE);
    // DrawText("6 - Get Shield or Full Sheild", 100.f, 400.f, 24.f, WHITE);
    // DrawText("7 - Shoot 3 Burst Bullets", 100.f, 450.f, 24.f, WHITE);
    // DrawText("8 - Hight Bullet Precision", 100.f, 500.f, 24.f, WHITE);

    vector<UpgradeOption> upgradeOptions = {
        {LoadTexture("./assets/graphics/ui/ability_ui/1.png"), "Auto Fire", 1},
        {LoadTexture("./assets/graphics/ui/ability_ui/2.png"), "Double Shot", 1},
        {LoadTexture("./assets/graphics/ui/ability_ui/3.png"), "Shift to Dash", 1},
        {LoadTexture("./assets/graphics/ui/ability_ui/4.png"), "Firerate +10%", 4},
        {LoadTexture("./assets/graphics/ui/ability_ui/5.png"), "Full Heal", -1},
        {LoadTexture("./assets/graphics/ui/ability_ui/6.png"), "Sheild", -1},
        {LoadTexture("./assets/graphics/ui/ability_ui/7.png"), "Triple Shot", 1},
        {LoadTexture("./assets/graphics/ui/ability_ui/8.png"), "Precision +10%", 4},
    };

    Font textFont = LoadFont("./assets/fonts/score.ttf");

public:
    void Update();
    void Draw();

    float current_x = 240.f;
    float current_y = 100.f;
    const float spacing = 40.f;
    const int columns = 2;
    int columnCount = 0;

    int pressedNumber = -1;
};