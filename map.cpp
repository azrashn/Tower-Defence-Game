#include "map.h"

Map::Map() {
   tileSize = 50.0f;
}

void Map::Update() {

}

Tile* Map::CheckTile(Vector2 mousePosition){

    int x = mousePosition.x / tileSize;
    int y = mousePosition.y / tileSize;

    if (x < 0 || y < 0 || x >= cols || y >= rows)
        return nullptr;

    return &grid[y][x];
}

void Map::Draw() {
    // Merkez kale 
    Rectangle castle = {
        400, 200, 600, 600
    };

    // Kale duvarı
    DrawRectangleLinesEx(castle, 8, DARKGRAY);

    // Town Hall 
    Rectangle townHall = {
        castle.x + 240,
        castle.y + 240,
        120,
        120
    };

    DrawRectangleRec(townHall, MAROON);
    DrawRectangleLinesEx(townHall, 3, BLACK);

    // Kapılar 
    DrawRectangle(castle.x + 260, castle.y - 20, 80, 20, BROWN);               // North
    DrawRectangle(castle.x + 260, castle.y + castle.height, 80, 20, BROWN);   // South

}