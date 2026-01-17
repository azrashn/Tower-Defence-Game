#include "map.h"
#include <iostream>
#include "constants.h"
#include <string>

// 0: Boş, 1: Duvar, 6: Yol, 3: Kule Yeri, 9: Hedef
const int ROWS_COUNT = 20;
const int COLS_COUNT = 36;

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
    {0,0,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,0,0,0,0,0,0,0,0,0,0,2,6,91,93,6,2,0,0},
    {0,2,6,6,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,6,92,94,6,2,0,0},
    {0,2,6,2,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,2,6,6,6,6,2,0,0},
    {0,2,6,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,6,2,2,2,2,0,0},
    {0,2,6,2,3,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,2,0,0,0,0,0},
    {0,2,6,2,3,3,3,3,3,3,3,3,3,2,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,0,0,0,0,0},
    {0,2,6,6,2,2,2,2,2,2,2,2,2,6,6,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
    {0,0,2,6,6,6,6,6,6,6,6,6,6,6,2,2,3,3,0,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int level2Data[ROWS_COUNT][COLS_COUNT] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,6,6,6,6,6,6,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,6,2,2,2,2,2,6,2,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,6,2,3,3,3,2,6,2,3,0,0,0,0,3,2,6,6,6,6,6,6,6,6,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,6,2,3,0,3,2,6,2,3,0,0,0,0,3,2,6,2,2,2,2,2,2,6,2,3,3,3,3,3,3,3,3,1,0},
    {0,1,6,2,3,3,3,2,6,2,3,0,0,0,0,3,2,6,2,3,3,3,3,2,6,2,3,0,0,0,0,0,0,3,1,0},
    {0,1,6,6,6,6,6,6,6,2,3,3,3,3,3,3,2,6,2,3,0,0,3,2,6,2,3,0,0,0,0,0,0,3,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,2,3,3,3,3,2,6,2,3,3,3,3,3,3,3,3,1,0},
    {0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,2,6,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,3,2,6,6,6,6,6,6,6,6,2,6,6,6,6,6,6,6,2,1,0},
    {0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,3,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,6,2,1,0},
    {0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,2,6,2,3,3,3,2,6,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,3,2,6,2,3,0,3,2,6,2,1,0},
    {0,1,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,3,2,6,2,3,3,3,2,6,2,1,0},
    {0,1,2,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,2,6,2,2,2,2,2,6,2,1,0},
    {0,1,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,3,3,3,2,6,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,9,3,2,6,2,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


Map::Map() {
    tileSize = (float)TILE_SIZE;
    currentGridW = COLS_COUNT;
    currentGridH = ROWS_COUNT;
    startX = 0;
    startY = 0;

    texWall = LoadTexture("assets/wall.png");
    texTree = LoadTexture("assets/Tree3.png");
    texRoad = LoadTexture("assets/Road.png");
    texTarget = LoadTexture("assets/target.png");
    texTowerSlot = LoadTexture("assets/tower_slot.png");
    texBackground = { 0 };

    LoadLevel(1); // Direkt 1. leveli yükle
}

Map::~Map() {
    UnloadTexture(texWall);
    UnloadTexture(texTree);
    UnloadTexture(texRoad);
    UnloadTexture(texTarget);
    UnloadTexture(texTowerSlot);
    if (texBackground.id != 0) UnloadTexture(texBackground);
}

void Map::Update() {}

void Map::LoadLevel(int levelIndex) {
    if (texBackground.id != 0) UnloadTexture(texBackground);

    // Arka plan resmini yine de yükleyelim, güzel dursun
    std::string bgPath = "assets/level" + std::to_string(levelIndex) + "_bg.png";
    texBackground = LoadTexture(bgPath.c_str());

    grid.clear(); // Izgarayı temizle

    // Bir pointer yardımıyla doğru diziyi seçiyoruz
    int (*selectedLevelData)[COLS_COUNT];

    if (levelIndex == 1) {
        selectedLevelData = level1Data;
    }
    else {
        // Varsayılan olarak Level 2 
        selectedLevelData = level2Data;
    }


    for (int y = 0; y < ROWS_COUNT; y++) {
        std::vector<Tile> currentRow;
        for (int x = 0; x < COLS_COUNT; x++) {

            // Veriyi diziden alıyoruz
            int tileTypeID = level1Data[y][x];

            Tile t;
            t.rect = { 0, 0, tileSize, tileSize };
            t.occupied = false;
            t.towerType = NONE;
            t.hasTree = false;
            t.id = tileTypeID;

            // Tip Belirleme (Switch-Case aynı kalabilir)
            switch (tileTypeID) {
            case 0: // Boş
                t.type = BLOCKED;
                t.color = BLANK;
                break;
            case 1: // Duvar
                t.type = BLOCKED; t.color = DARKGRAY;
                break;
            case 3: // Kule Yeri
                t.type = BUILDABLE; t.color = DARKBLUE;
                break;
            case 6: // Yol
                t.type = ROAD; t.color = Fade(ORANGE, 0.5f);
                break;
            case 9: // Hedef
                t.type = BLOCKED; t.color = RED;
                break;
     
            case 91: //  Sol Üst - Ana Parça
            case 92: //  Sağ Üst 
            case 93: //  Sol Alt 
            case 94: //  Sağ Alt 
                t.type = BLOCKED;
                t.color = BLANK; // Renk yok,  resim olacak
                break;

            default:
                t.type = BLOCKED; t.color = BLACK;
                break;
            }

            currentRow.push_back(t);
        }
        grid.push_back(currentRow);
    }

    // Koordinatları ayarla
    float mapWidthPx = currentGridW * tileSize;
    startX = (SCREEN_WIDTH - mapWidthPx) / 2.0f;
    startY = 0;

    for (int r = 0; r < currentGridH; r++) {
        for (int c = 0; c < currentGridW; c++) {
            Tile& t = grid[r][c];
            t.rect.x = (float)(startX + (c * tileSize));
            t.rect.y = (float)(startY + (r * tileSize));
            t.rect.width = tileSize;
            t.rect.height = tileSize;

            if (t.color.r == RED.r) townHallRect = t.rect;
        }
    }

}

Tile* Map::CheckTile(Vector2 position) {
    int x = (int)((position.x - startX) / tileSize);
    int y = (int)((position.y - startY) / tileSize);
    if (x >= 0 && x < currentGridW && y >= 0 && y < currentGridH) {
        return &grid[y][x];
    }
    return nullptr;
}

void Map::Draw() {

    if (texBackground.id != 0) {
        Rectangle source = { 0, 0, (float)texBackground.width, (float)texBackground.height };
        Rectangle dest = { startX, startY, (float)(currentGridW * tileSize), (float)(currentGridH * tileSize) };
        DrawTexturePro(texBackground, source, dest, { 0,0 }, 0.0f, WHITE);
    }
    else {
        DrawRectangle(startX, startY, currentGridW * tileSize, currentGridH * tileSize, DARKBROWN);
    }

    for (int y = 0; y < currentGridH; y++) {
        for (int x = 0; x < currentGridW; x++) {
            Tile& t = grid[y][x];
            if (t.id == 0) continue;

            //  Duvar 
            if (t.id == 1) {
                DrawTexturePro(texWall, { 0,0,(float)texWall.width,(float)texWall.height }, t.rect, { 0,0 }, 0, WHITE);
            }
            // Yol
            else if (t.type == ROAD) {
                DrawTexturePro(texRoad, { 0,0,(float)texRoad.width,(float)texRoad.height }, t.rect, { 0,0 }, 0, WHITE);
            }
                //  3.Kule yeri
            else if (t.id == 3) { 

                // Kule olsa da olmasa da bu zemin hep orada dursun
                DrawTexturePro(texTowerSlot,{ 0,0, (float)texTowerSlot.width, (float)texTowerSlot.height },t.rect, { 0,0 }, 0, WHITE);

                //  Eğer boşsa, beyaz noktayı çiz
                if (!t.occupied) {
                    Vector2 center = { t.rect.x + tileSize / 2, t.rect.y + tileSize / 2 };
                    DrawCircleV(center, 6, Fade(WHITE, 0.8f));
                }
            }
            else if (t.id == 91) { // ID 91: Target 

                // Hedef: (x, y) noktasından başla, 2 kare sağa, 2 kare aşağı yayıl.
                Rectangle destRect = {
                    t.rect.x,            // Başlangıç X
                    t.rect.y,           // Başlangıç Y
                    tileSize * 2.0f,   // Genişlik: 2 Kare
                    tileSize * 2.0f   // Yükseklik: 2 Kare
                };

                // Tek bir resmi (target.png) büyütüp o alana koyucaz
                DrawTexturePro(texTarget,{ 0, 0, (float)texTarget.width, (float)texTarget.height }, // Resmin tamamı
                    destRect,{ 0, 0 }, 0.0f, WHITE);     // Hedef: 2x2'lik alan
            }
             else if (t.id == 92 || t.id == 93 || t.id == 94) {  //diğer parçalar zaten diğerinin üzeirne çizildi
                continue;
             }
        }
    }
}
