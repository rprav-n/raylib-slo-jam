#include "raylib.h"

class Transition
{
public:
    Transition(float speed);

    void Update();
    void Draw();
    void Reset();

    bool IsComplete()
    {
        return transitionAlpha <= 0.0f;
    };

private:
    float transitionSpeed = {};
    float transitionAlpha = 1.f;
};