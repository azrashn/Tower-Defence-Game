#include "map.h"
#include "types.h"

static const int ROWS = 6;
static const int COLS = 12;
static const float TILE_SIZE = 60.0f;

static int levelData[ROWS][COLS] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // üstten giriş
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0 },
    { 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 0 },
    { 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0 }, // yatay dönüş
    { 0, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
    { 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }  // çıkış
};

Map::Map() {
    rows = ROWS;
    cols = COLS;
    tileSize = TILE_SIZE;

    backgroundTexture = LoadTexture("assets/level_bg.png");

    for (int y = 0; y < rows; y++) {
        std::vector<Tile> row;
        for (int x = 0; x < cols; x++) {
            Tile t;
            t.id = levelData[y][x];
            t.rect = { x * tileSize, y * tileSize, tileSize, tileSize };
            
            // ID → TYPE dönüşümü
            switch (t.id) {
            case 6:
                t.type = ROAD;
                t.color = ORANGE;
                break;
            case 3:
                t.type = BUILDABLE;
                t.color = BLUE;
                break;
            default:
                t.type = BLOCKED;
                t.color = DARKGRAY;
                break;
            }

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


bool Map::IsRoad(int gridX, int gridY) const {
    if (gridX < 0 || gridX >= cols || gridY < 0 || gridY >= rows)
        return false;

    return grid[gridY][gridX].type == ROAD;
}

void Map::Draw() {

    //Arka plan
    DrawTexture(backgroundTexture, 0, 0, WHITE);

    //Tile üst katmanı (debug / oyun mantığı)
     for (auto& row : grid) {
        for (auto& tile : row) {
            if (tile.type == ROAD) {
                DrawRectangleRec(tile.rect, Fade(ORANGE, 0.5f));
            }
            else if (tile.type == BUILDABLE) {
                DrawRectangleRec(tile.rect, Fade(BLUE, 0.5f));
            }
        }
    }

}