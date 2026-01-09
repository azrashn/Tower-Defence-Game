#include "enemy.h"
#include <cmath>

Enemy::Enemy() {
    path.push_back({ 50, 200 });
    path.push_back({ 300, 200 });
    path.push_back({ 300, 400 });

    position = path[0];
    currentTarget = 1;

    speed = 2.0f;
    active = true;

    maxHealth = 50.0f;
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

    if (fabs(position.x - target.x) < 1.0f &&
        fabs(position.y - target.y) < 1.0f) {
        position = target;
        currentTarget++;
    }
}

// Damage function
void Enemy::TakeDamage(float amount) {
    health -= amount;

    if (health <= 0) {
        health = 0;
        active = false; // Die if health is zero
    }
}

void Enemy::Draw() {
    if (!active) return;

    DrawCircleV(position, 8, RED);

    float hpRatio = health / maxHealth;
    DrawRectangle(
        position.x - 10,
        position.y - 18,
        20 * hpRatio,
        4,
        GREEN
    );
}
