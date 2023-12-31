#pragma once
#include "raylib.h"
#include "Settings.h"
#include <cstdio>

class Button
{

public:
    Button(Texture2D txtr, Vector2 pos);
    void Update();
    void Draw();

    bool btnAction = false;

private:
    Texture2D texture;

    float width = 0;
    float height = 0;

    Rectangle source = {};
    Vector2 position = {};
    Rectangle dest = {};
    Vector2 origin = {};

    Rectangle btnBounds = {};

    int btnState = 0; // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    Vector2 mousePoint = {0.0f, 0.0f};
};