#include "game.h"
#include "types.h"
#include "tower.h"
#include "enemy.h"
#include "raylib.h"

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;

    maxTargetHealth = 100.0f;
    targetHealth = maxTargetHealth;

    const int rawPath[][2] = {
    {6, 0},   // Başlangıç
    {6, 3},   // Aşağı in
    {7, 3},   // Sağa 
    {7, 4},   // Aşağı 
    {8, 4},   // Sağ
    {8, 5},   // Aşağı
    {17, 5},  // Uzun sağa gidiş
    {17, 10}, // Aşağı 
    {2, 10},  // Sola uzun dönüş
    {2, 17},  // Aşağı
    {14, 17}, // Sağa
    {14, 15}, // Yukarı 
    {29, 15}, // Sağa
    {29, 10}, // Yukarı
    {31, 10}  // Hedef
    };

    LoadPathFromGrid(rawPath, sizeof(rawPath) / sizeof(rawPath[0]));
}

void Game::LoadPathFromGrid(const int points[][2], int count) {
    levelPath.clear();

    for (int i = 0; i < count; i++) {
        float pixelX = points[i][0] * 40 + 20; //yarısı alınarak yolun ortasında durma mantığı
        float pixelY  = points[i][1] * 40 + 20;
        levelPath.push_back({ pixelX, pixelY });
    }
}

void Game::Update()
{
    map.Update();

    // Kule Tipi Seçimi
    static TowerType currentTowerType = ARCHER_TOWER;

    Vector2 mousePosition = GetMousePosition(); // mouse un ekrandaki pozisyonu hesapla
    mouseTile = map.CheckTile(mousePosition);

    static TowerType currentTowerType = ARCHER_TOWER;

    if (IsKeyPressed(KEY_A)) currentTowerType = ARCHER_TOWER;
    if (IsKeyPressed(KEY_S)) currentTowerType = MAGE_TOWER;
    if (IsKeyPressed(KEY_D)) currentTowerType = CANNON_TOWER;

    // Tower güncelle
    for (Tower& tower : towers)
    {
        tower.Update(enemies);
    }
    // Sol mouse butonu ile kule koymak için
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

    if (enemies.empty()) {
        enemies.push_back(Enemy(levelPath));
    }

    // Enemy güncellemek için
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].Update(); // özellikleri için ilerde  // index hangi düşman olduğunu gösteren

       if (!enemies[i].active) {
            // Hedefe ulaştı mı yoksa biz mi vurduk?
            if (enemies[i].GetHealth() > 0) {
                // Hedefe ulaştı, canımız yandı
                targetHealth -= enemies[i].GetDamageToTarget();
                if (targetHealth <= 0) {
                    targetHealth = 0;
                    gameOver = true;
                    }
                }
                else {
                    // Biz vurduk, para kazan
                    gold += enemies[i].GetReward();
            }
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
}

void Game::Reset() {  }


void Game::Draw()
{
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

    if (gameOver) {
        DrawText("GAME OVER", 400, 300, 40, RED);
    }
}
