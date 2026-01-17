#include "map.h"
#include "types.h"
#include <iostream>
#include "constants.h"
#include <string>

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
    tileSize = (float)TILE_SIZE;
    currentGridW = COLS_COUNT;
    currentGridH = ROWS_COUNT;
    startX = 0;
    startY = 0;

    texWall = LoadTexture("assets/wall.png");
    texTree = LoadTexture("assets/Tree3.png");
    texRoad = LoadTexture("assets/Road.png");
    texTarget = LoadTexture("assets/target.png");
    texBackground = { 0 };

    LoadLevel(1); // Direkt 1. leveli yükle
}

Map::~Map() {
    UnloadTexture(texWall);
    UnloadTexture(texTree);
    UnloadTexture(texRoad);
    UnloadTexture(texTarget);
    if (texBackground.id != 0) UnloadTexture(texBackground);
}

void Map::Update() {}

void Map::LoadLevel(int levelIndex) {
    if (texBackground.id != 0) UnloadTexture(texBackground);

    // Arka plan resmini yine de yükleyelim, güzel dursun
    std::string bgPath = "assets/level" + std::to_string(levelIndex) + "_bg.png";
    texBackground = LoadTexture(bgPath.c_str());

    grid.clear(); // Izgarayı temizle


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

            if (t.id == 1) DrawTexturePro(texWall, { 0,0,(float)texWall.width,(float)texWall.height }, t.rect, { 0,0 }, 0, WHITE);
            // Yol, Hedef, Ağaç 
            if (t.type == ROAD) DrawTexturePro(texRoad, { 0,0,(float)texRoad.width,(float)texRoad.height }, t.rect, { 0,0 }, 0, WHITE);

            if (t.type == BUILDABLE && !t.occupied) {
                Vector2 center = { t.rect.x + tileSize / 2, t.rect.y + tileSize / 2 };
                DrawCircleV(center, 6, Fade(WHITE, 0.8f));
            }
        }
    }
}
