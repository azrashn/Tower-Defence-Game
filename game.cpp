#include "game.h"
#include "tower.h"
#include "enemy.h"
#include "types.h"
#include "raylib.h"

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;

    mouseTile = nullptr;

    enemies.push_back(Enemy(GOBLIN)); // enemy ekleme ve çağırma


}

void Game::Update()
{
    map.Update();

    Vector2 mousePosition = GetMousePosition(); // mouse un ekrandaki pozisyonu hesapla
    mouseTile = map.CheckTile(mousePosition);


    // Tower güncelle
    for (Tower& tower : towers)
    {
        tower.Update(enemies);
    }
    // Sol mouse butonu ile kule koymak için
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (mouseTile != nullptr) {
            if (mouseTile->type ==  TileType::BUILDABLE && !mouseTile->occupied) {

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

    // Enemy güncellemek için
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].Update(); // özellikleri için ilerde  // index hangi düşman olduğunu gösteren

        if (!enemies[i].active)
        {
            enemies.erase(enemies.begin() + i);  // vectorün indexini silmek ve vektör ilerlemesini sabit tutmak için
            i--;
        }
    }
}


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
