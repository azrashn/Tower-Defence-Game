#include "raylib.h"
#include "game.h"

enum GameState {
    MENU,       // Ana Menü
    GAMEPLAY,   // Oyun Oynanıyor
    PAUSED,     //duraklama
    GAME_OVER   // bitirme
};

int main()
{    // dinamik ayarlama için
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Castle Defense - Map Test");
    SetTargetFPS(60);

    Game game;
    GameState currentState = MENU;
 
    while (!WindowShouldClose())
    {
        game.Update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}