#include "raylib.h"
#include "Bullet.h"
#include "Booster.h"
#include "Settings.h"
#include <vector>

using namespace std;

class Player
{

public:
    Player(Vector2 pos);
    Vector2 GetMovementDirection();
    void Update(double dt);
    void Draw();
    void CheckCollisionBounds();
    void ShootBullet();

    Vector2 GetPosition();
    float GetRotation();
    Vector2 GetVectorRotation();

private:
    Texture2D texture = LoadTexture("./assets/graphics/ships/green_ship.png");
    Texture2D red_bullet = LoadTexture("./assets/graphics/bullets/red_bullet.png");

    float acceleration = 10.f;
    float speed = 5.f;
    Vector2 velocity = {0.0f, 0.0f};
    float rotation = 0.f;
    float rotationSpeed = 200.0f;

    float width = 0.f;
    float height = 0.f;

    float scaledWidth = 0.f;
    float scaledHeight = 0.f;

    Rectangle source = Rectangle{texture.width / 3.f, 0.f, texture.width / 3.f, (float)texture.height};
    Vector2 position = {100.f, 100.f};
    Rectangle dest = Rectangle{position.x, position.y, source.width *Settings::SCALE, (float)source.height *Settings::SCALE};
    Vector2 centerOrigin = {};
    Vector2 topLeftOrigin = {};
    Vector2 boosterPos = {};
    Vector2 origin = {};
    vector<Bullet> bullets;
    Booster booster = Booster();
};