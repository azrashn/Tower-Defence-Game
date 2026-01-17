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

    // Yavaşlatma değişkenleri başlangıç değeri
    isSlowed = false;
    slowTimer = 0.0f;

    // 1. Yol Bilgisini Kaydet
    this->pathPoints = pathPoints;
    this->type = t;  // enemy Türü için

    // Başlangıç pozisyonu
    if (!pathPoints.empty()) {
        position = pathPoints[0];
    }
    else {
        position = { -100, -100 };
    }

    active = true;
    currentTargetIndex = 1;
    radius = 12.0f; // Varsayılan boyut

    // Türe Göre Güç Ayarlama 
    switch (type) {
    case GOBLIN:
        baseSpeed = 4.0f;   // Hız
        maxHealth = 60.0f;   //Can
        damageToTarget = 5.0f; // Target hasar
        goldReward = 10;     // kazanılan Altın
        radius = 10.0f;  // büyüklüğü
        break;

    case ORC:
        baseSpeed = 2.0f;          
        maxHealth = 160.0f;      
        damageToTarget = 20.0f; 
        goldReward = 25;        
        radius = 16.0f;         
        break;

    case BOSS:
        baseSpeed = 1.0f;          
        maxHealth = 1000.0f;     
        damageToTarget = 100.0f; 
        goldReward = 200;       
        radius = 26.0f;         
        break;
    }

    currentSpeed = baseSpeed; // Oyun başlarken hızı orijinal hıza eşitle
    health = maxHealth; // Canı fulle
}

// yavaşlatma
void Enemy::ApplySlow(float factor, float duration) {

    isSlowed = true;
    slowTimer = duration; // Süreyi başlat (örneğin 2.0 saniye)

    // Hızı düşür 
    currentSpeed = baseSpeed * factor;
}

void Enemy::Update() {
    // Eğer düşman aktif değilse veya yol listesi boşsa işlem yapma
    if (!active || pathPoints.empty()) return;

    // yavaşlama süresi -> Her güncellemede (frame) süreyi azaltıyoruz 
    if (isSlowed) {
        slowTimer -= GetFrameTime(); //  geçen zamanı 

        if (slowTimer <= 0) {
            // Süre bitti, işlemleri normale döndürüyoruz
            isSlowed = false;
            currentSpeed = baseSpeed; // Hız eski haline döner
        }
    }

    // Hedef bitti mi?
    if (currentTargetIndex >= pathPoints.size()) {
        active = false;
        return;
    }

    // mevcut hedefimiz
    Vector2 target = pathPoints[currentTargetIndex];

    // 1. X Ekseninde Hareket (Sağa/Sola)
    // Eğer hedef sağdaysa  x'i artır
    if (position.x < target.x) {
        position.x += currentSpeed;
        // Hedefi geçmesin diye yavaşla karakterlerin titreme olayını çözüyor
        if (position.x > target.x) position.x = target.x;
    }
    // Eğer hedef soldaysa  x'i azalt
    else if (position.x > target.x) {
        position.x -= currentSpeed;
        if (position.x < target.x) position.x = target.x;
    }

    // 2. Y Ekseninde Hareket -> hedef aşağıdaysa Y'yi artır
    if (position.y < target.y) {
        position.y += currentSpeed;
        if (position.y > target.y) position.y = target.y;
    }
    // Eğer hedef yukarıdaysa Y'yi azalt
    else if (position.y > target.y) {
        position.y -= currentSpeed;
        if (position.y < target.y) position.y = target.y;
    }

    //  Hedefe Vardık mı Kontrolü
    // X farkı 1'den küçük VE Y farkı 1'den küçükse vardmşızdır.
    if (abs(position.x - target.x) < 1.0f && abs(position.y - target.y) < 1.0f) {

        // Konumu tam hedefin üstüne oturt 
        position = target;
        currentTargetIndex++;
    }
}

void Enemy::Draw() {
    if (!active) return;

    // Renk seçimi enemy
    Color color = GREEN; // Varsayılan

    if (type == GOBLIN) color = LIME;       // Açık Yeşil
    else if (type == ORC) color = DARKGREEN; // Koyu Yeşil
    else if (type == BOSS) color = PURPLE;   // Mor

    // eğer büyücü sonrası yavaşlamışsa 
    if (isSlowed) {
        color = SKYBLUE; // Buz mavisi
    }
    // Temsili yuvarlak çizimi
    DrawCircle((int)position.x, (int)position.y, (float)radius, color);
    DrawCircleLines((int)position.x, (int)position.y, (float)radius, BLACK);

    // can barı
    float hpPercent = health / maxHealth;
    DrawRectangle(position.x - 10, position.y - 15, 20 * hpPercent, 4, GREEN);
}

void Enemy::TakeDamage(float amount) {
    health -= amount;
    if (health <= 0) {
        active = false; // Öldü
    }
}