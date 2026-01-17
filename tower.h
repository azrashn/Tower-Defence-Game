#pragma once
#include "raylib.h"
#include "enemy.h"
#include "types.h"
#include <vector>

// Basit mermi yapısı
struct Bullet {
    Vector2 position;
    Vector2 targetPos;
    float speed;
    float damage;
    bool active;
};

class Tower {
public:
    Tower(Vector2 pos, TowerType t);

    void Update(std::vector<Enemy>& enemies);
    void Draw();

    Vector2 position;
    TowerType type;

private:
    float range;
    float damage;
    float fireCooldown;
    float cooldownTimer;

    Enemy* targetEnemy;
    std::vector<Bullet> bullets;
};
