#include "tower.h"
#include "raymath.h" 
#include <iostream>


// Değişkenleri tanımlama
Texture2D Tower::texArcher = { 0 };
Texture2D Tower::texMage = { 0 };
Texture2D Tower::texCannon = { 0 };

// Resmleri Yükleme Fonksiyonu
void Tower::InitTextures() {
    texArcher = LoadTexture("assets/tower_archer.png");
    texMage = LoadTexture("assets/tower_mage.png");
    texCannon = LoadTexture("assets/tower_cannon.png");
}

// Resimleri Silme Fonksiyonu
void Tower::UnloadTextures() {
    UnloadTexture(texArcher);
    UnloadTexture(texMage);
    UnloadTexture(texCannon);
}

Tower::Tower(Vector2 pos, TowerType t) {
    position = pos;
    type = t;
    level = 1; // seviye 1 başlar

    upgradeCost = 150;
    cooldownTimer = 0.0f;
    targetEnemy = nullptr;

    if (type == ARCHER_TOWER) {
        damage = 8;
        fireCooldown = 0.8f; 
        range = 150.0f;
        bulletSpeed = 6.0f;  
        upgradeCost = 100;  
    }
    else if (type == MAGE_TOWER) {
        damage = 30;         //  hasar
        fireCooldown = 2.5f; // dolumma süresi
        range = 220.0f;      // menzil
        bulletSpeed = 3.0f;  // mermi süzülür
        upgradeCost = 300;   // yükseltme fiyatı
    }
    else if (type == CANNON_TOWER) {
        damage = 16; 
        fireCooldown = 1.5f; 
        range = 130.0f; 
        bulletSpeed = 4.5f;
        upgradeCost = 200;
    }

    if (type == ARCHER_TOWER) totalSpent = 100;
    else if (type == MAGE_TOWER) totalSpent = 300;
    else if (type == CANNON_TOWER) totalSpent = 200;
}

// Kuleyi Güncelleme Fonksiyonu
void Tower::Upgrade() {

    int cost = GetUpgradeCost(); // Upgrade maliyeti
    totalSpent += cost;          

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

    //  MERMİLERİ HAREKET ETTİRME TASARIMI
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].active) {

            // Eğer kilitlendiğimiz düşman hala yaşıyorsa, hedefi güncelle -> Takip Et
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

    //  ATEŞ ETME MANTIĞI 
    if (cooldownTimer > 0) {  // Silahı Soğut
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

                if (type == CANNON_TOWER) {
                    float explosionRadius = 70.0f; // Patlama çapı (ne kadar geniş vuracağı)

                    // Tüm düşmanları kontrol et: Hedefin yakınındakiler de hasar yesin
                    for (Enemy& subEnemy : enemies) {
                        if (subEnemy.active) {
                            // Hedef düşmana olan mesafesi 70 birimden az olan herkesi vur
                            if (Vector2Distance(subEnemy.position, enemy.position) <= explosionRadius) {
                                subEnemy.TakeDamage(damage);
                            }
                        }
                    }
                    std::cout << "BOOM!Area damage dealt" << std::endl;
                }
                // 2. DİĞER KULELER İSE TEK HEDEFİ VUR
                else {
                    enemy.TakeDamage(damage);
                }

                //  Hasar verme (Anlık vuruş - Hitscan)
                enemy.TakeDamage(damage);

                // Eğer ateş eden kule BÜYÜCÜ ise yavaşlatma uygula
                if (type == MAGE_TOWER) {
                    // Hızı %50 (0.5f) düşür ve 2.0 saniye sürsün
                    enemy.ApplySlow(0.5f, 2.0f);
                }

                //  mermi oluşturma görsel olarak
                Bullet b;
                b.position = position;
                b.targetPos = enemy.position;
                b.lockedEnemy = &enemy;       // Düşmana kilitlenme
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
   
    // KULE TİPİNE GÖRE RESİM SEÇİMİ
    Texture2D* currentTex = &texArcher; // Varsayılan

    if (type == MAGE_TOWER) {
        currentTex = &texMage;
    }
    else if (type == CANNON_TOWER) {
        currentTex = &texCannon;
    }

    //MENZİL ÇİZİMİ
    DrawCircleLines((int)position.x, (int)position.y, range, Fade(DARKGRAY, 0.4f));// Hafif şeffaf gri bir daire 

    // KULE GÖVDESİ 
    Rectangle sourceRec = { // Resmin tamamını alarak kullanıyoruz
        0.0f, 0.0f,
        (float)currentTex->width,
        (float)currentTex->height
    };

    Rectangle destRec = { // hangi boyutta belirtmek için
        position.x,
        position.y,
        16.0f,
        16.0f
    };

    // Merkezi Resmin tam ortasını, pozisyonun üzerine, tile'ın yarısı 
    Vector2 origin = { 8.0f, 8.0f };

    // Resmi Çiz
    DrawTexturePro(*currentTex, sourceRec, destRec, origin, 0.0f, WHITE);

    // Kulenin biraz üzerine seviyesini yazalım
    DrawText(TextFormat("Lvl %d", level), (int)position.x - 10, (int)position.y - 30, 10, BLACK);

    //  MERMİLERİ ÇİZ
    for (const Bullet& b : bullets) {
        if (b.active) {
            if (b.type == ARCHER_TOWER) {
                // Okçu mermisi: Küçük Kahverengi nokta
                DrawCircleV(b.position, 4, BROWN);
            }
            else if (b.type == MAGE_TOWER) {
                // Büyücü mermisi: Parlak mor küre
                DrawCircleV(b.position, 6, VIOLET);
            }
            else if (b.type == CANNON_TOWER) {
                // Topçu mermisi: Kare veya büyük siyah gülle
                DrawCircleV(b.position, 5, DARKGRAY);
            }
        }
    }
}

