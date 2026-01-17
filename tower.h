#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "raylib.h"
#include "enemy.h"
#include "types.h"
#include <vector>

class Tower {
public:
    Tower(Vector2 pos, TowerType t);
    void Update(std::vector<Enemy>& enemies);
    void Draw();

    //  Kuleyi geliştir
    void Upgrade();

    // Yükseltme maliyetini sor (UI'da göstermek için)
    int GetUpgradeCost() const { return upgradeCost; }
    int GetLevel() const { return level; }
    int GetSellRefund() const;

    Vector2 position;
    TowerType type;

    int level;          // Kule Seviyesi (1, 2, 3...)
    float range;        // Menzil
    float damage;       // Hasar
    float fireCooldown;   // Atış bekleme süresi
    float bulletSpeed;    // Mermi hızı
    float cooldownTimer;

    int upgradeCost;    // Bir sonraki seviye için gereken para
    int totalSpent;

    Enemy* targetEnemy;

    std::vector<Bullet> bullets; // Kulenin attığı mermiler
};

#endif