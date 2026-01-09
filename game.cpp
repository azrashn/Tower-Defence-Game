#include "game.h"
#include "raylib.h"

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;

    mouseTile = nullptr;
    lastMouseTile = nullptr; // Bir önceki frame’deki tile
    selectedTile = nullptr;

    mouseTime = 0.0f;  // Mouse aynı tile üzerinde durma süresi
}

void Game::Update()
{
    map.Update();

    Vector2 mousePosition = GetMousePosition(); // mouse un ekrandaki pozisyonu hesapla
    mouseTile = map.CheckTile(mousePosition); // tile bul

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

}

void Game::Draw()
{
   // Haritayı çizme fonksiyonu
    map.Draw();

    // Basit UI 
    DrawText(" Game ", 20, 20, 20, DARKGRAY);
    DrawText(TextFormat("Gold: %d", gold), 20, 50, 20, GOLD);

    if (selectedTile) {
    DrawRectangleLinesEx(selectedTile->rect, 3, BLUE); // seçili tile vurgulamak için
    }

    if (gameOver) {
        DrawText("GAME OVER", 400, 300, 40, RED);
    }
}
