#include "game.h"
#include "raylib.h"

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;

    mouseTile = nullptr;
    lastMouseTile = nullptr; // Bir önceki frame’deki tile

    mouseTime = 0.0f;  // Mouse aynı tile üzerinde durma süresi
    selectedTileCount = 0;
}

void Game::Update()
{
    map.Update();

}

void Game::Draw()
{
   // Haritayı çizme fonksiyonu
    map.Draw();

    // Basit UI 
    DrawText(" Game ", 20, 20, 20, DARKGRAY);
    DrawText(TextFormat("Gold: %d", gold), 20, 50, 20, GOLD);

    if (gameOver) {
        DrawText("GAME OVER", 400, 300, 40, RED);
    }
}
