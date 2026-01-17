#include "tower.h"
#include "raymath.h"

Tower::Tower(Vector2 pos, TowerType t) {
    position = pos;
    type = t;
    level = 1;

    range = 140.0f;
    fireCooldown = 1.0f;
    cooldownTimer = 0;
    targetEnemy = nullptr;

    //  Türlere göre basit farklar
    if (type == ARCHER_TOWER) {
        damage = 15;
        range = 150.0f;
        damage = 15.0f;
        fireCooldown = 0.8f;
    }
    else if (type == MAGE_TOWER) {
        damage = 60;  
        range = 200.0f;
        damage = 40.0f;
        fireCooldown = 2.0f;
    }
    else { // CANNON
        damage = 40; 
        range = 130.0f;
        damage = 30.0f;
        fireCooldown = 1.5f;
    }
}

void Tower::Update(std::vector<Enemy>& enemies) {

    // 1. Mermileri güncelle
    for (int i = 0; i < bullets.size(); i++) {
        if (!bullets[i].active) {
            bullets.erase(bullets.begin() + i);
            i--;
            continue;
        }

        bullets[i].position =
            Vector2MoveTowards(bullets[i].position,
                               bullets[i].targetPos,
                               bullets[i].speed);

        if (Vector2Distance(bullets[i].position,
                            bullets[i].targetPos) < 5.0f) {
            bullets[i].active = false;
        }
    }

     // 2. Cooldown azalt
    if (cooldownTimer > 0)
        cooldownTimer -= GetFrameTime();

    targetEnemy = nullptr;

    // 3. Hedef bul + ateş et
    for (Enemy& enemy : enemies) {
        if (!enemy.active) continue;

        float dist = Vector2Distance(position, enemy.position);
        if (dist <= range) {

            targetEnemy = &enemy;

            if (cooldownTimer <= 0) {

                // HASAR VER
                enemy.TakeDamage(damage);

                // MERMİ OLUŞTUR (görsel)
                Bullet b;
                b.position = position;
                b.targetPos = enemy.position;
                b.speed = 6.0f;
                b.damage = damage;
                b.active = true;

                bullets.push_back(b);

                cooldownTimer = fireCooldown;
            }
            break;
        }
    }

    for (Bullet& b : bullets) {
        if (!b.active) continue;

        b.position = Vector2MoveTowards(b.position, b.targetPos, b.speed);
        if (Vector2Distance(b.position, b.targetPos) < 4)
            b.active = false;
    }
}

void Tower::Draw() {
     // 1. Menzil
      DrawCircleLines((int)position.x, (int)position.y, range, Fade(DARKGRAY, 0.4f) );

    // 2. Kule gövdesi
    Color c = GRAY;
    if (type == ARCHER_TOWER) c = BLUE;
    if (type == MAGE_TOWER)  c = PURPLE;
    else if (type == CANNON_TOWER) towerColor = RED;

    DrawCircleLines(position.x, position.y, range, Fade(GRAY, 0.3f));
    DrawRectangle(position.x - 16, position.y - 16, 32, 32, c);

       if (targetEnemy) {
        DrawLineV(position, targetEnemy->position, RED);
    }

    // 3. Mermiler
    for (Bullet& b : bullets){ 
        if (b.active){ 
            DrawCircleV(b.position, 4, BLACK);
        }
    }
}
