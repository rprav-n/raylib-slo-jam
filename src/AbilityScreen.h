#include "raylib.h"
#include "Settings.h"
#include <vector>

using namespace std;

struct UpgradeOption
{
    Texture2D texture;
    const char *description;
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
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Auto Shoot"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Double Bullet"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Dashing"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Increase Auto Shoot Speed by 10%"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Full Health"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Get Shield or Full Sheild"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Shoot 3 Burst Bullets"},
        {LoadTexture("./assets/graphics/ui/ability_ui/auto_shoot.png"), "Hight Bullet Precision"},
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
};