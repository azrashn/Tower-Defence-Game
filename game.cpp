#include "game.h"
#include "raylib.h"

Game::Game() {
    gold = 500;       // Oyuncunun başlangıç para değeri
    gameOver = false;
}

void Game::Update()
{
 
}

void Game::Draw()
{
  
    // Basit UI 
    DrawText(" Game ", 20, 20, 20, DARKGRAY);
    DrawText(TextFormat("Gold: %d", gold), 20, 50, 20, GOLD);

    if (gameOver) {
        DrawText("GAME OVER", 400, 300, 40, RED);
    }
}
