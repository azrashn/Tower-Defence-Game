#include "game.h"
#include "tower.h"
#include "wave.h"
#include <iostream>
#include <string> 


const int pathLevel1[][2] = {
   //sağa - aşağı
    {19, 0},   
    {19, 23},  
    {39, 23},  
    {39, 31},  
    {62, 21},  
    {75, 21},  
    {75, 6} 
};

Game::Game() {
    gold = 500;
    maxTargetHealth = 100.0f;
    targetHealth = maxTargetHealth;
    gameOver = false;
    
    Tower::InitTextures();

    LoadLevel(1);
}

Game::~Game() {
    // Oyun kapanırken resimleri temizle
    Tower::UnloadTextures();
}

// Grid koordinatlarından alıp piksele çevriliyor
void Game::LoadPathFromGrid(const int points[][2], int count) {
    levelPath.clear();
    for (int i = 0; i < count; i++) {
        float pixelX = points[i][0] * 40 + 20; // Otomatik hesaplıyor
        float pixelY = points[i][1] * 40 + 20; 
        levelPath.push_back({ pixelX, pixelY });
    }
}

void Game::LoadLevel(int levelNumber) {
    currentLevel = levelNumber;

    // Harita görselini değiştir 
    map.LoadLevel(currentLevel);

    // Yeni level temiz başlasın
    enemies.clear();
    towers.clear(); 
    wave = WaveManager(); // Dalgayı sıfırla
    wave.Init();

    // 3. Doğru Yolu Yükle
    if (currentLevel == 1) {
        LoadPathFromGrid(pathLevel1, sizeof(pathLevel1) / sizeof(pathLevel1[0]));
    }
    else if (currentLevel == 2) {
        //LoadPathFromGrid(pathLevel2, sizeof(pathLevel2) / sizeof(pathLevel2[0]));
    }

    // Oyuncuyu bilgilendir
    std::cout << "Level " << currentLevel << " Uploaded!" << std::endl;
}

void Game::Update() {
    
    map.Update();

    // Level Değiştirme butonu
    if (IsKeyPressed(KEY_L)) {
        if (currentLevel == 1) LoadLevel(2);
        else LoadLevel(1);
    }

    // Kule Tipi Seçimi
    static TowerType currentTowerType = ARCHER_TOWER;

    if (IsKeyPressed(KEY_A)) currentTowerType = ARCHER_TOWER;
    if (IsKeyPressed(KEY_S)) currentTowerType = MAGE_TOWER;
    if (IsKeyPressed(KEY_D)) currentTowerType = CANNON_TOWER;

    if (!gameOver) {

        // Wave Sistem Tasarımı
        wave.Update(enemies, levelPath);;

          //  Enemy güncelle 
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i].Update();

            if (!enemies[i].active) {
                // Hedefe ulaştı mı yoksa biz mi vurduk?
                if (enemies[i].GetHealth() > 0) {
                    // Hedefe ulaştı, canımız azaldı
                    targetHealth -= enemies[i].GetDamageToTarget();
                    if (targetHealth <= 0) {
                        targetHealth = 0;
                        gameOver = true;
                    }
                }
                else {
                    // Biz öldürdük, para kazandık
                    gold += enemies[i].GetReward();
                }
                enemies.erase(enemies.begin() + i);
                i--;
            }
        }

        // Kuleleri Güncelle
        for (Tower& tower : towers) {
            tower.Update(enemies);
        }

        // Sol tık ile kule inşa ediyoruz
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Tile* clickedTile = map.CheckTile(mousePos);

            if (clickedTile != nullptr) {
                if (clickedTile->type == BUILDABLE && !clickedTile->occupied) {
                    if (towers.size() < MAX_INNER_TOWERS) {

                        int cost = 0;
                        if (currentTowerType == ARCHER_TOWER) cost = 100;
                        else if (currentTowerType == MAGE_TOWER) cost = 300;
                        else if (currentTowerType == CANNON_TOWER) cost = 200;

                        if (gold >= cost) {
                            gold -= cost;
                            clickedTile->occupied = true;
                            clickedTile->type = TOWER;

                            Vector2 towerPos = {
                                clickedTile->rect.x + TILE_SIZE / 2.0f,
                                clickedTile->rect.y + TILE_SIZE / 2.0f
                            };
                            towers.push_back(Tower(towerPos, currentTowerType));
                        }
                    }
                }
            }
        }

        // Sağ mouse tık ile kuleleri güncelliyoruz
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            for (Tower& tower : towers) {
                if (CheckCollisionPointCircle(mousePos, tower.position, 20)) {
                    int cost = tower.GetUpgradeCost();
                    if (gold >= cost) {
                        gold -= cost;
                        tower.Upgrade();
                    }
                }
            }
        }

        // X tuşu ile kuleleri satıyoruz
        if (IsKeyPressed(KEY_X)) {
            Vector2 mousePos = GetMousePosition();
            for (auto it = towers.begin(); it != towers.end(); ++it) {
                if (CheckCollisionPointCircle(mousePos, it->position, 20)) {
                    int refund = it->GetSellRefund();
                    gold += refund;

                    Tile* tile = map.CheckTile(it->position);
                    if (tile) {
                        tile->occupied = false;
                        tile->type = BUILDABLE; // Eski haline döndür
                    }
                    towers.erase(it);
                    break;
                }
            }
        }
    }
}

void Game::Reset() {
    gold = 500;
    targetHealth = maxTargetHealth;
    gameOver = false;

    enemies.clear(); // Tüm düşmanları sil
    towers.clear();  // Tüm kuleleri sil

    wave = WaveManager(); // Wave sınıfının constructor'ını tekrar çağırarak sıfırlıyoruz
    wave.Init();

    LoadLevel(1);
}

void Game::Draw() {
    //  Haritayı Çiz
    map.Draw();

    //  enemy Çiz
    for (Enemy& enemy : enemies) {
        enemy.Draw();
    }

    // Kuleleri Çiz
    for (Tower& tower : towers) {
        tower.Draw();
    }

    // Arayüz Çizimi
    int uiY = 820;

    DrawText("TOWER DEFENSE", 20, uiY, 30, SKYBLUE);
    DrawText(TextFormat("Gold: %d G", gold), 350, uiY + 5, 24, GOLD);
    DrawText(TextFormat("Tower: %d/%d", (int)towers.size(), MAX_INNER_TOWERS), 550, uiY + 5, 24, WHITE);

    // Can Barı Rengi
    float hpPercent = (targetHealth / maxTargetHealth) * 100;
    Color hpColor = GREEN;
    if (hpPercent < 50) hpColor = ORANGE;
    if (hpPercent < 20) hpColor = RED;
    DrawText(TextFormat("Target HP: %.0f%%", hpPercent), 800, uiY + 5, 24, hpColor);

    wave.Draw();

    // Bilgilendirme
    DrawText("[A]Archer  [S]Magician  [D]Artilleryman", 1050, uiY + 5, 20, LIGHTGRAY);
    DrawText("[RIGHT CLICK]Upgrade  [X]Sell", 1050, uiY + 30, 20, LIGHTGRAY);

    DrawLine(0, 800, GetScreenWidth(), 800, DARKGRAY);

    // Game Over (Bir sonraki eklenecek victory)
    if (gameOver) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
        const char* title = "GAME OVER";
        int titleW = MeasureText(title, 60);
        DrawText(title, (GetScreenWidth() - titleW) / 2, 300, 60, RED);
    }
}