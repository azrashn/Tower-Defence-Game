#pragma once
#include "map.h"
#include "enemy.h"
#include <vector>

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
};
