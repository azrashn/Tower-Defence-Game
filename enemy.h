#pragma once
#include "raylib.h"
#include <vector>
#include "types.h"

class Enemy {
public:
    Enemy(EnemyType type);
    
    // geçici süreliğine eklendi
    Enemy(const std::vector<Vector2>& pathPoints);

    if (type == GOBLIN) {
        speed = 3.5f;
        maxHealth = 40.0f;
        radius = 8.0f;
    }
    else if (type == ORC) {
        speed = 2.0f;
        maxHealth = 90.0f;
        radius = 12.0f;
    }

    health = maxHealth;
}

void Enemy::Update() {
    if (!active || path.empty()) return;

    if (currentTarget >= path.size()) {
        active = false;
        return;
    }

    Vector2 target = path[currentTarget];

    if (position.x < target.x) position.x += speed;
    else if (position.x > target.x) position.x -= speed;

    if (position.y < target.y) position.y += speed;
    else if (position.y > target.y) position.y -= speed;

    if (fabs(position.x - target.x) <= speed &&
        fabs(position.y - target.y) <= speed) {
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

    DrawCircleV(position, radius, bodyColor);
    DrawCircleLines(position.x, position.y, radius, BLACK);

    float hpRatio = health / maxHealth;
    DrawRectangle(
        position.x - 12,
        position.y - 20,
        24 * hpRatio,
        4,
        GREEN
    );
}