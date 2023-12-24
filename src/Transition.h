#include "raylib.h"

class Transition
{
public:
    Transition(float speed) : transitionSpeed(speed), transitionAlpha(1.0f) {}

    void Update()
    {
        transitionAlpha -= GetFrameTime() / transitionSpeed;

        if (transitionAlpha < 0.0f)
            transitionAlpha = 0.0f;
    }

    void Draw() const
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transitionAlpha));
    }

    bool IsComplete() const
    {
        return transitionAlpha <= 0.0f;
    }

private:
    float transitionSpeed;
    float transitionAlpha;
};