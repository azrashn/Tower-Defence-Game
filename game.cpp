#include "game.h"
#include "types.h"
#include "tower.h"
#include "enemy.h"
#include "raylib.h"
#include "wave.h" // <--- EKLENDİ: Wave sistemini dahil ettik

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;

    maxTargetHealth = 100.0f;
    targetHealth = maxTargetHealth;

    mouseTile = nullptr;

    const int rawPath[][2] = { // dönüş yerleri hesaplanarak ilerleme sağlanıyor.
        {0, 1},   // Başlangıç Sol taraf, 1. satır
        {10, 1},  // Sağa kadar git
        {10, 3},  // Aşağı in -> 3. satıra
        {1, 3},   // Sola kadar gel
        {1, 5},   // Aşağı in -> 5. satır
        {11, 5}   // Bitiş 
    };

    LoadPathFromGrid(rawPath, 6); // kaç adet olduğu

    // <--- EKLENDİ: Dalga sistemini (WaveManager) başlatıyoruz.
    // Bu fonksiyon 1. dalgayı hazırlar.
    waveManager.Init();
}

void Game::Update() {
    // Oyun bittiyse (Kaybettiysek) durdur
    if (gameOver) return;

    map.Update();

    Vector2 mousePosition = GetMousePosition(); // mouse un ekrandaki pozisyonu hesapla
    mouseTile = map.CheckTile(mousePosition);

    static TowerType currentTowerType = ARCHER_TOWER;

    if (IsKeyPressed(KEY_A)) currentTowerType = ARCHER_TOWER;
    if (IsKeyPressed(KEY_S)) currentTowerType = MAGE_TOWER;

    // Tower güncelle
    for (Tower& tower : towers)
    {
        tower.Update(enemies);
    }

    // Sol mouse butonu ile kule koymak için
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (mouseTile != nullptr) {
            if (mouseTile->type == TileType::BUILDABLE && !mouseTile->occupied) {

                // (İleride buraya if (gold >= 100) kontrolü eklenecek)
                mouseTile->occupied = true;
                mouseTile->type = TileType::TOWER;

                Vector2 towerPos = {
                    mouseTile->rect.x + mouseTile->rect.width / 2,
                    mouseTile->rect.y + mouseTile->rect.height / 2
                };

                towers.push_back(Tower(towerPos, ARCHER_TOWER));
            }
        }
    }

    // <--- DEĞİŞTİ: Eski manuel spawn kodu silindi.
    // Artık düşman üretimini WaveManager yönetiyor.
    if (!waveManager.IsVictory()) {
        waveManager.Update(enemies, levelPath);
    }

    // Enemy güncellemek ve silmek için
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].Update();

        // Düşman öldü mü veya aktifliği bitti mi?
        if (!enemies[i].active)
        {
            // (İleride buraya gold += 20; eklenecek)
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
}

void Game::Reset() {
    // Reset mantığı ileride buraya eklenebilir
}

void Game::LoadPathFromGrid(const int points[][2], int count) {
    levelPath.clear();

    for (int i = 0; i < count; i++) {
        float px = points[i][0] * 40 + 20; //yarısı alınarak yolun ortasında durma mantığı
        float py = points[i][1] * 40 + 20;
        levelPath.push_back({ px, py });
    }
}

void Game::Draw() {
    // Haritayı çizme fonksiyonu
    map.Draw();

    if (mouseTile != nullptr)
    {
        DrawRectangleLinesEx(mouseTile->rect, 2, YELLOW);
    }

    // kuleleri çiz
    for (Tower& tower : towers) {
        tower.Draw();
    }

    // Enemy çiz
    for (Enemy& enemy : enemies)
    {
        enemy.Draw();
    }

    // Basit UI 
    DrawText(" Game ", 20, 20, 20, DARKGRAY);
    DrawText(TextFormat("Gold: %d", gold), 20, 50, 20, GOLD);

    // <--- EKLENDİ: Wave bilgisini ekrana yazdır (Örn: WAVE: 1 / 5)
    waveManager.Draw();

    // Oyun Sonu ve Zafer Ekranları
    if (gameOver) {
        DrawText("GAME OVER", 400, 300, 40, RED);
    }
    else if (waveManager.IsVictory()) {
        // <--- EKLENDİ: Zafer durumu kontrolü
        DrawText("VICTORY!", 400, 300, 50, GREEN);
    }
}