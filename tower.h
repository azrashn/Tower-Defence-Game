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

    // Yükseltme maliyetini sorma 
    int GetUpgradeCost() const {
        return upgradeCost;
    }
    int GetLevel() const {
        return level; 
    }

    int GetSellRefund() const;

    Vector2 position;
    TowerType type;

    int level;          // Kule Seviyesi 
    float range;        // Menzil
    float damage;       // Hasar
    float fireCooldown;   // Atış bekleme süresi
    float bulletSpeed;    // Mermi hızı
    float cooldownTimer;

    int upgradeCost;    // Bir sonraki seviye için gereken para
    int totalSpent;

    Enemy* targetEnemy;

    std::vector<Bullet> bullets; // Kulenin attığı mermiler

    // Bu fonksiyonları Game sınıfında çağırıp asset yüklenecek
    static void InitTextures();   // Resimleri yükle
    static void UnloadTextures(); // Resimleri sil

    static Texture2D texArcher;
    static Texture2D texMage;
    static Texture2D texCannon;
};
#endif