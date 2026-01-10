#include "game.h"
#include "raylib.h"

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;

    mouseTile = nullptr;
    lastMouseTile = nullptr; // Bir önceki frame’deki tile
    selectedTile = nullptr;

    mouseTime = 0.0f;  // Mouse aynı tile üzerinde durma süresi

    enemies.push_back(Enemy()); // enemy ekleme
}

void Game::Update()
{
    map.Update();

    Vector2 mousePosition = GetMousePosition(); // mouse un ekrandaki pozisyonu hesapla
    mouseTile = map.CheckTile(mousePosition); 

    // Mouse aynı tile üzerindeyse süre artsın
    if (mouseTile && mouseTile == lastMouseTile)
    {
       mouseTime += GetFrameTime(); // Son çizilen frama ile önceki arasındaki süre belirlemek için 60FPS
    }
    else // diğer türlü tile süresini sıfırla
    {
      mouseTime = 0.0f;
      lastMouseTile = mouseTile;
    }

    if (mouseTile && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Click yapısı tile ile
         selectedTile = mouseTile; // yapılan click anını adreste saklıyor. Amaç tıklandığı anda tile seçmek
    }

    for (int i = 0; i < enemies.size(); i++) { 
        enemies[i].Update();  // özellikleri için ilerde  // index hangi düşman olduğunu gösteren

        if (!enemies[i].active) { 
            enemies.erase(enemies.begin() + i); // vectorün indexini silmek ve vektör ilerlemesini sabit tutmak için
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

    // Basit UI 
    DrawText(" Game ", 20, 20, 20, DARKGRAY);
    DrawText(TextFormat("Gold: %d", gold), 20, 50, 20, GOLD);

    if (gameOver) {
        DrawText("GAME OVER", 400, 300, 40, RED);
    }
}
