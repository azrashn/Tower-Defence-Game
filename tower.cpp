#include "tower.h"
#include "raymath.h" 
#include <iostream>

Tower::Tower(Vector2 pos, TowerType t) {
    position = pos;
    type = t;
    level = 1;          // Seviye 1 başlar

    upgradeCost = 150;
    cooldownTimer = 0.0f;
    targetEnemy = nullptr;

    if (type == ARCHER_TOWER) {
        damage = 15;
        fireCooldown = 0.8f; // Hızlı ateş
        range = 150.0f;
        bulletSpeed = 8.0f;  // Ok hızlı gider
        upgradeCost = 100;   // Okçu daha ucuz olsun
    }
    else if (type == MAGE_TOWER) {
        damage = 60;         // Yüksek hasar
        fireCooldown = 2.5f; // Yavaş dolum
        range = 220.0f;      // Daha uzun menzil
        bulletSpeed = 5.0f;  // Büyü topu yavaş süzülür
        upgradeCost = 300;   // Büyücü pahalı olsun
    }
    else if (type == CANNON_TOWER) {
        damage = 40; // Orta-Yüksek hasar
        fireCooldown = 1.5f; // Orta hız
        range = 130.0f; // Kısa menzil
        bulletSpeed = 6.0f;
        upgradeCost = 200;
    }

    // Fiyatları buraya manuel yazıyoruz veya sabitlerden çekiyoruz
    if (type == ARCHER_TOWER) totalSpent = 100;
    else if (type == MAGE_TOWER) totalSpent = 300;
    else if (type == CANNON_TOWER) totalSpent = 200;
}

// KULEYİ GÜncelleme FONKSİYONU
void Tower::Upgrade() {

    int cost = GetUpgradeCost(); // Upgrade maliyeti neyse
    totalSpent += cost;          // Toplam harcamaya ekle

    level++;            // Seviye atla
    damage += 15.0f;    // Hasarı artır
    range += 20.0f;     // Menzili uzat

    // Ateş hızını artır
    if (fireCooldown > 0.2f) {
        fireCooldown *= 0.9f;
    }

    upgradeCost += 100;
    std::cout << "Kule Upgrade Edildi! Yeni Level: " << level << std::endl;
}

void Tower::Update(std::vector<Enemy>& enemies) {

    // --- BÖLÜM 1: MERMİLERİ HAREKET ETTİR (GÜDÜMLÜ SİSTEM) ---
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].active) {

            // Eğer kilitlendiğimiz düşman hala yaşıyorsa, hedefi güncelle (Takip Et)
            if (bullets[i].lockedEnemy != nullptr &&
                bullets[i].lockedEnemy->active &&
                bullets[i].lockedEnemy->GetHealth() > 0) {

                bullets[i].targetPos = bullets[i].lockedEnemy->position;
            }

            // Mermiyi hedefe doğru yürüt
            bullets[i].position = Vector2MoveTowards(bullets[i].position, bullets[i].targetPos, bullets[i].speed);

            // Hedefe ulaştı mı?
            if (Vector2Distance(bullets[i].position, bullets[i].targetPos) < 5.0f) {
                bullets[i].active = false; // Mermiyi yok et
            }
        }
        else {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }

    // --- BÖLÜM 2: ATEŞ ETME MANTIĞI ---

    // Silahı Soğut
    if (cooldownTimer > 0) {
        cooldownTimer -= GetFrameTime();
    }

    targetEnemy = nullptr;

    for (Enemy& enemy : enemies) {
        if (!enemy.active) continue;

        // Mesafe hesapla
        float dist = Vector2Distance(position, enemy.position);

        if (dist <= range) {
            targetEnemy = &enemy;

            // Ateş Etme Hazır mı?
            if (cooldownTimer <= 0) {

                // 1. HASAR VER (Anlık vuruş - Hitscan)
                enemy.TakeDamage(damage);

                // Eğer ateş eden kule BÜYÜCÜ ise yavaşlatma uygula
                if (type == MAGE_TOWER) {
                    // Hızı %50 (0.5f) düşür ve 2.0 saniye sürsün
                    enemy.ApplySlow(0.5f, 2.0f);
                }

                // 2. MERMİ OLUŞTUR (Görsel Efekt)
                Bullet b;
                b.position = position;
                b.targetPos = enemy.position;
                b.lockedEnemy = &enemy;       // Düşmana kilitlen! (types.h'da eklediğimiz pointer)
                b.speed = bulletSpeed;
                b.damage = damage;
                b.active = true;
                b.type = type;

                bullets.push_back(b);

                // 3. Silahı tekrar doldur
                cooldownTimer = fireCooldown;
            }
            break;
        }
    }
}

int Tower::GetSellRefund() const {
    return (int)(totalSpent * 0.30f); // %30 iade
}

void Tower::Draw() {
    // 1. Kule Rengini Belirle
    Color towerColor = GRAY;
    if (type == ARCHER_TOWER) towerColor = BLUE;
    else if (type == MAGE_TOWER) towerColor = PURPLE;
    else if (type == CANNON_TOWER) towerColor = RED;

    // 2. Menzil Çizimi (ARTIK GÖRÜNÜR)
    // Hafif şeffaf gri bir daire
    DrawCircleLines((int)position.x, (int)position.y, range, Fade(DARKGRAY, 0.5f));

    // 3. Kule Gövdesi (Kare)
    DrawRectangle((int)position.x - 16, (int)position.y - 16, 32, 32, towerColor);
    DrawRectangleLines((int)position.x - 16, (int)position.y - 16, 32, 32, BLACK); // Siyah çerçeve

    // 4. Seviye Yazısı
    DrawText(TextFormat("Lvl %d", level), (int)position.x - 10, (int)position.y - 30, 10, WHITE);

    // 5. MERMİLERİ ÇİZ
    for (const Bullet& b : bullets) {
        if (b.active) {
            if (b.type == ARCHER_TOWER) {
                DrawCircleV(b.position, 4, BLACK);
            }
            else if (b.type == MAGE_TOWER) {
                DrawCircleV(b.position, 6, VIOLET);
            }
            else if (b.type == CANNON_TOWER) {
                DrawRectangle(b.position.x - 5, b.position.y - 5, 10, 10, BLACK);
            }
        }
    }
}

