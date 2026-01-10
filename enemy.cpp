#include "enemy.h"
#include <cmath>

Enemy::Enemy(EnemyType t) {
    type = t;

    path.push_back({ 50, 200 });
    path.push_back({ 300, 200 });
    path.push_back({ 300, 400 });

    position = path[0];
    currentTarget = 1;
    active = true;

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
