#pragma once
#include "map.h"

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
};
