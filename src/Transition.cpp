#include "Transition.h"

Transition::Transition(float speed)
{
    transitionSpeed = speed;
}

void Transition::Reset()
{
    transitionAlpha = 1.f;
}

void Transition::Update()
{
    {
        transitionAlpha -= GetFrameTime() / transitionSpeed;

        if (transitionAlpha < 0.0f)
            transitionAlpha = 0.0f;
    }
}

void Transition::Draw()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transitionAlpha));
}