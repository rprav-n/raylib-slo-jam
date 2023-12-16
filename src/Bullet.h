#include "raylib.h"
#include "Settings.h"

class Bullet
{
public:
    Bullet(Texture txt, Vector2 pos, Vector2 dir, float rot);
    bool IsOutOfBounds();
    void Update(float dt);
    void Draw();
    Rectangle GetRect();
    bool IsQueueFree()
    {
        return queueFree;
    };
    void SetQueueFree(bool val)
    {
        queueFree = val;
    };

private:
    Texture2D texture;
    Rectangle rect = {};
    Vector2 position = {0.f, 0.f};
    Rectangle dest = {};
    Vector2 origin = {};
    float rotation = 0.f;
    int speed = 800;
    Vector2 direction = {};
    bool queueFree = false;
};
