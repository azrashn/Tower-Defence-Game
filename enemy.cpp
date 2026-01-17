#include "enemy.h"
#include <cmath>
#include "raylib.h"

Enemy::Enemy(EnemyType t, const std::vector<Vector2>& pathPoints) {
    type = t;
    path = pathPoints;

    if (!path.empty()) {
        position = path[0];
    }
    else {
        position = { 0, 0 };
    }

    currentTarget = 1;
    active = true;

    // Yavaşlatma sıfırla
    isSlowed = false;
    slowTimer = 0.0f;

    // SADECE GOBLIN VE ORC AYARLARI (BOSS YOK)
    if (type == GOBLIN) {
        baseSpeed = 3.5f;
        maxHealth = 40.0f;
        damageToTarget = 5.0f;
        goldReward = 10;
        radius = 8.0f;
    }
    else { // ORC ve diğerleri
        baseSpeed = 2.0f;
        maxHealth = 90.0f;
        damageToTarget = 20.0f;
        goldReward = 25;
        radius = 12.0f;
    }

    currentSpeed = baseSpeed;
    health = maxHealth;
}

void Enemy::ApplySlow(float factor, float duration) {
    isSlowed = true;
    slowTimer = duration;
    currentSpeed = baseSpeed * factor;
}

void Enemy::Update() {
    if (!active || path.empty()) return;

    if (isSlowed) {
        slowTimer -= GetFrameTime();
        if (slowTimer <= 0) {
            isSlowed = false;
            currentSpeed = baseSpeed;
        }
    }

    if (currentTarget >= path.size()) {
        active = false;
        return;
    }

    Vector2 target = path[currentTarget];

    // Hareket
    if (position.x < target.x) position.x += currentSpeed;
    else if (position.x > target.x) position.x -= currentSpeed;

    if (position.y < target.y) position.y += currentSpeed;
    else if (position.y > target.y) position.y -= currentSpeed;

    if (fabs(position.x - target.x) <= currentSpeed &&
        fabs(position.y - target.y) <= currentSpeed) {
        position = target;
        currentTarget++;
    }
}

void Enemy::TakeDamage(float amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        active = false;
    }
}

void Enemy::Draw() {
    if (!active) return;

    Color bodyColor = RED;
    if (type == GOBLIN) bodyColor = LIME;
    else bodyColor = DARKGREEN; // ORC

    if (isSlowed) bodyColor = SKYBLUE;

    DrawCircleV(position, radius, bodyColor);
    DrawCircleLines(position.x, position.y, radius, BLACK);

    // Can Barı
    float hpRatio = health / maxHealth;
    DrawRectangle(position.x - radius, position.y - radius - 10, radius * 2, 6, RED);
    DrawRectangle(position.x - radius, position.y - radius - 10, (radius * 2) * hpRatio, 6, GREEN);
}