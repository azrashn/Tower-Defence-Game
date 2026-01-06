#include "enemy.h"

Enemy::Enemy() {
    position = { 50, 200 }; // Sabit başlangıç noktası
    speed = 2.0f;
    active = true;
}

void Enemy::Update() {
    if (!active) return;

    // Sadece sağa doğru hareket
    position.x += speed;

    // Ekranın dışına çıkınca sil
    if (position.x > GetScreenWidth()) {
        active = false;
    }
}

void Enemy::Draw() {
    if (!active) return;

    DrawCircleV(position, 8, RED);
}
