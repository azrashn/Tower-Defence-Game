#include "map.h"
#include <iostream>
#include "constants.h"
#include <string>
#include "LevelData.h"

Map::Map() {
    tileSize = (float)TILE_SIZE;
    currentGridW = COLS;
    currentGridH = ROWS;
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

    int rows = 0;
    int cols = 0;

    if (levelIndex == 1) {
        rows = LEVEL1_ROWS;
        cols = LEVEL1_COLS;
    }
    else if (levelIndex == 2) {
        
    }
    currentGridH = rows;
    currentGridW = cols;

    for (int y = 0; y < rows; y++) {
        std::vector<Tile> currentRow;
        for (int x = 0; x < cols; x++) {

            int tileTypeID = 0;

            // Veriyi doğru diziden çek
            if (levelIndex == 1) {
                tileTypeID = level1Data[y][x];
            }
            else {
               
            }
    
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

                //  Eğer boşsa, beyaz noktayı çiz
                if (!t.occupied) {
                    Vector2 center = { t.rect.x + tileSize / 2.0f, t.rect.y + tileSize / 2.0f };
                    DrawCircleV(center, 2.0f, Fade(WHITE, 0.5f));
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
