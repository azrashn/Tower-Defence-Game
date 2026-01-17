#include "enemy.h"
#include "raymath.h" 
#include <cmath>

Enemy::Enemy(std::vector<Vector2> pathPoints, EnemyType t) {

    baseSpeed = 0.0f;
    currentSpeed = 0.0f;
    maxHealth = 0.0f;
    health = 0.0f;
    damageToTarget = 0.0f;
    goldReward = 0;

    isSlowed = false;
    slowTimer = 0.0f;

    this->pathPoints = pathPoints;
    this->type = t;

    if (!pathPoints.empty()) {
        position = pathPoints[0];
    }
    else {
        position = { -100, -100 };
    }

    active = true;
    currentTargetIndex = 1;
    radius = 12.0f;

    switch (type) {
    case GOBLIN:
        baseSpeed = 4.0f;
        maxHealth = 30.0f;
        damageToTarget = 5.0f;
        goldReward = 10;
        radius = 10.0f;
        break;

    case ORC:
        baseSpeed = 2.0f;
        maxHealth = 80.0f;
        damageToTarget = 20.0f;
        goldReward = 25;
        radius = 14.0f;
        break;

    case BOSS:
        baseSpeed = 1.0f;
        maxHealth = 500.0f;
        damageToTarget = 100.0f;
        goldReward = 200;
        radius = 20.0f;
        break;
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
    if (!active || pathPoints.empty()) return;

    if (isSlowed) {
        slowTimer -= GetFrameTime();

        if (slowTimer <= 0) {
            isSlowed = false;
            currentSpeed = baseSpeed;
        }
    }

    if (currentTargetIndex >= pathPoints.size()) {
        active = false;
        return;
    }

    Vector2 target = pathPoints[currentTargetIndex];

    if (position.x < target.x) {
        position.x += currentSpeed;
        if (position.x > target.x) position.x = target.x;
    }
    else if (position.x > target.x) {
        position.x -= currentSpeed;
        if (position.x < target.x) position.x = target.x;
    }

    if (position.y < target.y) {
        position.y += currentSpeed;
        if (position.y > target.y) position.y = target.y;
    }
    else if (position.y > target.y) {
        position.y -= currentSpeed;
        if (position.y < target.y) position.y = target.y;
    }

    if (abs(position.x - target.x) < 1.0f && abs(position.y - target.y) < 1.0f) {

        position = target;
        currentTargetIndex++;
    }
}

void Enemy::Draw() {
    if (!active) return;

    Color color = RED;

    if (type == GOBLIN) color = LIME;
    else if (type == ORC) color = DARKGREEN;
    else if (type == BOSS) color = PURPLE;

    if (isSlowed) {
        color = SKYBLUE;
    }
    DrawCircle((int)position.x, (int)position.y, (float)radius, color);
    DrawCircleLines((int)position.x, (int)position.y, (float)radius, BLACK);

    float hpPercent = health / maxHealth;
    DrawRectangle(position.x - 10, position.y - 15, 20 * hpPercent, 4, GREEN);
}

void Enemy::TakeDamage(float amount) {
    health -= amount;
    if (health <= 0) {
        active = false;
    }
}