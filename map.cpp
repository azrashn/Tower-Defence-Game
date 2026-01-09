#include "map.h"

static const int ROWS = 6;
static const int COLS = 12;
static const float TILE_SIZE = 60.0f;

static int levelData[ROWS][COLS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map() {
    rows = ROWS;
    cols = COLS;
    tileSize = TILE_SIZE;

    for (int y = 0; y < rows; y++) {
        std::vector<Tile> row;
        for (int x = 0; x < cols; x++) {
            Tile t;
            t.id = levelData[y][x];
            t.rect = { x * tileSize, y * tileSize, tileSize, tileSize };
            row.push_back(t);
        }
        grid.push_back(row);
    }

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
     for (auto& row : grid) {
        for (auto& tile : row) {
            Color c = tile.id == 1 ? DARKGRAY : LIGHTGRAY;
            DrawRectangleRec(tile.rect, c);
            DrawRectangleLinesEx(tile.rect, 1, BLACK);
        }
    }

}