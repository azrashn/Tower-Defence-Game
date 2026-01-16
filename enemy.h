#pragma once
#include "raylib.h"
#include <vector>

enum EnemyType {
    GOBLIN,
    ORC,
    BOSS  
};

class Enemy {
public:
    Enemy(EnemyType type);

    void Update();
    void Draw();
    void TakeDamage(float amount);

    // Yavaşlatma
    void ApplySlow(float factor, float duration);

    float GetDamageToTarget() const { return damageToTarget; }
    int GetGoldReward() const { return goldReward; }

    bool active;
    Vector2 position;

private:
    std::vector<Vector2> path;
    int currentTarget;

    EnemyType type;

    // Hareket
    float baseSpeed;     
    float currentSpeed;  

    // Yavaşlatma durumu
    bool isSlowed;       
    float slowTimer;     

    float health;
    float maxHealth;
    float radius;

    float damageToTarget;
    int goldReward;
};
