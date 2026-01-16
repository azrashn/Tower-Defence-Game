#include "enemy.h"
#include <cmath>

Enemy::Enemy(EnemyType t) {
    type = t;

    // TEST YOLU 
    path.push_back({ 50, 200 });
    path.push_back({ 300, 200 });
    path.push_back({ 300, 400 });

    position = path[0];
    currentTarget = 1;
    active = true;

    // Yavaşlatma başlangıç
    isSlowed = false;
    slowTimer = 0.0f;

     switch (type) {

    case GOBLIN:
        baseSpeed = 3.5f;
        maxHealth = 40.0f;
        damageToTarget = 5.0f;
        goldReward = 10;
        radius = 8.0f;
        break;

    case ORC:
        baseSpeed = 2.0f;
        maxHealth = 90.0f;
        damageToTarget = 20.0f;
        goldReward = 25;
        radius = 12.0f;
        break;

    case BOSS: // 
        baseSpeed = 1.0f;
        maxHealth = 400.0f;
        damageToTarget = 80.0f;
        goldReward = 150;
        radius = 20.0f;
        break;
    }

    currentSpeed = baseSpeed;
    health = maxHealth;
}

// YAVAŞLATMA
void Enemy::ApplySlow(float factor, float duration) {
    isSlowed = true;
    slowTimer = duration;
    currentSpeed = baseSpeed * factor;
}

void Enemy::Update() {
    if (!active || path.empty()) return;

    // YAVAŞLATMA SÜRESİ
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

    if (position.x < target.x) position.x += currentSpeed;
    else if (position.x > target.x) position.x -= currentSpeed;

    if (position.y < target.y) position.y += currentSpeed;
    else if (position.y > target.y) position.y -= currentSpeed;

    if (fabs(position.x - target.x) < 1.0f &&
        fabs(position.y - target.y) < 1.0f) {
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
    else if (type == ORC) bodyColor = DARKGREEN;
    else bodyColor = PURPLE; // BOSS

    // Yavaşlamışsa maviye çevir
    if (isSlowed) bodyColor = SKYBLUE;

    DrawCircleV(position, radius, bodyColor);
    DrawCircleLines(position.x, position.y, radius, BLACK);

    // CAN BARI
    float hpRatio = health / maxHealth;
    DrawRectangle(position.x - radius, position.y - radius - 8,
                  (radius * 2) * hpRatio, 5, GREEN);
}
