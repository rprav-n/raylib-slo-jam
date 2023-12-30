#pragma once
#include "raylib.h"

class Helper
{
public:
    float GetRandomFloat(float min, float max)
    {
        return min + (float)GetRandomValue(0, 10000) / 10000.0f * (max - min);
    };
};
