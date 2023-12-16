#include "raylib.h"
#include "Settings.h"

class Enemy
{

private:
    Texture2D texture = LoadTexture("./assets/graphics/enemies/basic_enemy.png");
    float scaledWidth = texture.width * Settings::SCALE;
    float scaledHeight = texture.height * Settings::SCALE;
    Rectangle source = {0.f, 0.f, (float)texture.width, (float)texture.height};
    Vector2 position = {100.f, 100.f};
    Rectangle dest = {position.x, position.y, scaledWidth, scaledHeight};
    Vector2 origin = {scaledWidth / 2.f, scaledHeight / 2.f};
    float speed = 100.f;
    float rotation = 0.f;

public:
    void Update(double dt, Vector2 playerPosition, float rot);
    void Draw();
};