#pragma once
#include "raylib.h"
#include <vector>
#include "types.h" // <--- DÜZELTME: EnemyType tanımını buradan alacak

// SİLİNDİ: enum EnemyType { ... } bloğu kaldırıldı çünkü types.h içinde zaten var.
// Bu işlem "redefinition" (yeniden tanımlama) hatasını çözer.

class Enemy {
public:
    // Constructor: Hem Tip hem de Yol (path) alıyor (WaveManager ile uyumlu)
    Enemy(EnemyType type, const std::vector<Vector2>& pathPoints);

    void Update();
    void Draw();
    void TakeDamage(float amount);

    // Yeni Özellikler: Yavaşlatma
    void ApplySlow(float factor, float duration);

    // Getter Fonksiyonları
    float GetDamageToTarget() const { return damageToTarget; }
    int GetGoldReward() const { return goldReward; }

    bool active;
    Vector2 position;

    // Draw ve çarpışma kontrolü için public değişkenler
    float radius;
    float health;
    float maxHealth;

private:
    std::vector<Vector2> path;
    int currentTarget;

    EnemyType type;

    // Hareket Sistemi
    float baseSpeed;     // Düşmanın normal hızı
    float currentSpeed;  // Yavaşlayınca düşen anlık hızı

    // Yavaşlatma Durumu
    bool isSlowed;
    float slowTimer;

    // Ödül ve Hasar
    float damageToTarget;
    int goldReward;
};