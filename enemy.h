#pragma once
#include "raylib.h"
#include <vector>

enum EnemyType {
    GOBLIN,
    ORC
};

class Enemy {
public:
    Enemy(EnemyType type);

    void Update();
    void Draw();
    void TakeDamage(float amount);

    bool active;
    Vector2 position;

private:
    std::vector<Vector2> path;
    int currentTarget;

    EnemyType type;

    float speed;
    float health;
    float maxHealth;
    float radius;
};
