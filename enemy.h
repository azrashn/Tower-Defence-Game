#pragma once
#include "raylib.h"
#include <vector>
#include "types.h"

class Enemy {
public:
    Enemy(EnemyType type);
    
    // geçici süreliğine eklendi
    Enemy(const std::vector<Vector2>& pathPoints);

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
