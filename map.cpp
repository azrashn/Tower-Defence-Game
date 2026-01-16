#include "map.h"
#include "types.h"

const int ROWS_COUNT = 20;
const int COLS_COUNT = 36;
static const float TILE_SIZE = 60.0f;

int level1Data[ROWS_COUNT][COLS_COUNT] = {
    {0,0,0,0,0,2,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,6,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,6,6,2,2,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,6,6,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,2,2,6,6,6,6,6,6,6,6,6,6,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,6,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,6,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,2,6,2,3,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0},
    {0,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,6,6,2,3,0,0,0,2,2,2,2,2,2,6,6,6,6,2,0,0},
    {0,0,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,0,0,0,0,0,0,0,0,0,0,2,6,9,9,6,2,0,0},
    {0,2,6,6,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,6,9,9,6,2,0,0},
    {0,2,6,2,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,2,6,6,6,6,2,0,0},
    {0,2,6,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,6,2,2,2,2,0,0},
    {0,2,6,2,3,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,2,0,0,0,0,0},
    {0,2,6,2,3,3,3,3,3,3,3,3,3,2,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,0,0,0,0,0},
    {0,2,6,6,2,2,2,2,2,2,2,2,2,6,6,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
    {0,0,2,6,6,6,6,6,6,6,6,6,6,6,2,2,3,3,0,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map() {
    tileSize = TILE_SIZE;
    rows = ROWS;
    cols = COLS;

    backgroundTexture = LoadTexture("assets/level_bg.png");

    t.occupied = false;

    for (int y = 0; y < rows; y++) {
        std::vector<Tile> row;
        for (int x = 0; x < cols; x++) {

            Tile t;
            t.id = levelData[y][x];
            t.rect = { x * tileSize, y * tileSize, tileSize, tileSize };

            switch (t.id) {

            case 6: // GERÇEK YOL
                t.type = ROAD;
                t.color = Fade(ORANGE, 0.6f);
                break;

            case 2: // SAHTE YOL (sadece görsel)
                t.type = BLOCKED;
                t.color = Fade(ORANGE, 0.3f);
                break;

            case 5: // GİZLİ YOL (oyuncu görmez)
                t.type = ROAD;
                t.color = Fade(GREEN, 0.25f);
                break;

            case 3: // KULE YERİ
                t.type = BUILDABLE;
                t.color = Fade(BLUE, 0.4f);
                break;

            default: // BOŞ / GEÇİLMEZ
                t.type = BLOCKED;
                t.color = BLANK;
                break;
            }

            row.push_back(t);
        }
        grid.push_back(row);
    }
}

void Map::Update() {

}



Tile* Map::CheckTile(Vector2 mousePosition) {

    int gridX = (int)(mousePosition.x / tileSize);
    int gridY = (int)(mousePosition.y / tileSize);

    if (gridX < 0 || gridX >= cols || gridY < 0 || gridY >= rows)
        return nullptr;

    return &grid[gridY][gridX];
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

                 //Kule yeri işareti
                Vector2 center = {
                    tile.rect.x + tileSize / 2,
                    tile.rect.y + tileSize / 2
                };
                DrawCircleV(center, 4, WHITE);
            }
        }
    }

}