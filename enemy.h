#pragma once
#include "raylib.h"

class Enemy {
public:
    Enemy();

    void Update();
    void Draw();

    bool active;
    Vector2 position;

private:
    float speed;
};
