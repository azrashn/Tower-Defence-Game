#pragma once
#include "raylib.h"
#include "types.h"
#include <vector>
#include "types.h" // <--- DÜZELTME: EnemyType tanımını buradan alacak

class Enemy {
public:
    Enemy(std::vector<Vector2> pathPoints, EnemyType type);

    void Update();
    void Draw();
    void TakeDamage(float amount);

    void ApplySlow(float factor, float duration);

    float GetHealth() const { return health; }
    float GetDamageToTarget() const { return damageToTarget; }
    int GetReward() const { return goldReward; }

    bool active;
    Vector2 position;

    // Draw ve çarpışma kontrolü için public değişkenler
    float radius;
    float health;
    float maxHealth;

private:
    std::vector<Vector2> pathPoints;
    int currentTargetIndex;
    float radius;

    EnemyType type;

    float baseSpeed; 
    float currentSpeed;

    bool isSlowed;    
    float slowTimer;      
    float health;
    float maxHealth;
    float damageToTarget;
    int goldReward;
};