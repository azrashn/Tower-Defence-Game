#include "raylib.h"
#include "game.h"
#include "constants.h"

enum GameState {
    MENU,       // Ana Menü
    GAMEPLAY,   // Oyun Oynanıyor
    PAUSED,     //duraklama
    GAME_OVER   // bitirme
};

int main() {
    // Pencereyi sabit boyutta aç
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defense");

    SetTargetFPS(60);

    Game game;
    GameState currentState = MENU; // Oyun Menü ile başlar

    // Oyun döngüsü
    while (!WindowShouldClose()) {

        switch (currentState) {

            // Ana Menü
        case MENU:
            if (IsKeyPressed(KEY_ENTER)) {
                game.Reset(); // Yeni oyun için her şeyi sıfırla
                currentState = GAMEPLAY;
            }
            break;

            // Oyun Tuşları P , P VEYA R, M
        case GAMEPLAY:
            // P tuşuna basılırsa PAUSE moduna geç
            if (IsKeyPressed(KEY_P)) {
                currentState = PAUSED;
            }

            // Oyun bitti mi kontrolü
            if (game.gameOver) {
            }
            else {
                game.Update(); // Sadece PAUSE DEĞİLSE güncelle
            }
            break;

        case PAUSED:
            // P veya R tuşuna basılırsa devam et oyuna
            if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_R)) {
                currentState = GAMEPLAY;
            }
            // M tuşuna basılırsa Menüye dön
            if (IsKeyPressed(KEY_M)) {
                currentState = MENU;
            }
            break;
        }

        // Draw
        ClearBackground(RAYWHITE);

        switch (currentState) {

            // Menü tasarımı 
        case MENU:
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKBLUE); // Arka plan
            DrawText("TOWER DEFENSE", 380, 200, 60, WHITE);
            DrawText("Press[ENTER] to Start", 530, 500, 30, LIGHTGRAY);
            DrawText("To exit, press[ESC]", 620, 600, 20, GRAY);
            break;

        case GAMEPLAY:
            game.Draw(); // Oyunun kendi çizim fonksiyonu
            break;

            // pause çizimi
        case PAUSED:
            game.Draw(); 

            // Üzerine yarı saydam siyah bir perde çek
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4f));

            // Pause Menüsü Yazıları
            DrawText("GAME PAUSED", 400, 300, 50, WHITE);
            DrawText("[R] - Resume", 480, 450, 30, GREEN);
            DrawText("[M] - Return to Main Menu", 490, 500, 30, RED);
            break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}