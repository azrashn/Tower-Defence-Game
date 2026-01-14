#pragma once
#include "map.h"
#include "enemy.h"
#include <vector>
#include "raylib.h"
#include "tower.h"

class Game
{
public:
    Game();
    void Update();
    void Draw();

private:
    Map map; // nesne 

    int gold;        // Oyuncu parası 
    bool gameOver;   // Oyun durumu bitmişmi onu bilip yazdırmak amaçlanıyor
     
    // Mapde tile seçimi için gereken tanımlamalar
    Tile* mouseTile;;
    Tile* lastMouseTile;
    Tile* selectedTile;

    float mouseTime;

    std::vector<Enemy> enemies;
    std::vector<Tower> towers;

     void LoadPathFromGrid(const int points[][2], int count);
};
