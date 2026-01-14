#pragma once
#include "raylib.h"
#include "enemy.h"
#include <vector>

enum TowerType {
    ARCHER_TOWER,
    MAGE_TOWER
};

class Tower {
public:
    Tower(Vector2 pos, TowerType t);
    void Update(std::vector<Enemy>& enemies);
    void Draw();

    Vector2 position;
    TowerType type;
    float range;

    Enemy* targetEnemy;
};
