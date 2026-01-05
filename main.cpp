#include "raylib.h"
#include "game.h"

int main()
{
    InitWindow(1400, 1000, "Castle Defense - Map Test");
    SetTargetFPS(60);

    Game game;

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