#pragma once
#include "raylib.h"
#include <vector>

class Enemy {
public:
    Enemy();

    void Update();
    void Draw();
    void TakeDamage(float amount);

    bool active;
    Vector2 position;

private:
    std::vector<Vector2> path;
    int currentTarget;
    float speed;

 
    float health;
    float maxHealth;
};
