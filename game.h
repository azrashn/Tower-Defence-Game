#pragma once
#include "map.h"
#include "enemy.h"
#include <vector>
#include "raylib.h"
#include "tower.h"
#include "constants.h"

class Game{
public:
    Game();
    void Update();
    void Draw();
    void Reset(); // Oyunu sıfırlama fonksiyonu

    bool gameOver; // Oyun durumu bitmişmi onu bilip yazdırmak amaçlanıyor

private:
    Map map; // nesne 
    std::vector<Enemy> enemies;
    std::vector<Tower> towers;

    //  Düşmanların izleyeceği sabit rota
    std::vector<Vector2> levelPath;

    int gold; // Oyuncu parası 
    const int MAX_INNER_TOWERS = 8;

    float targetHealth;      // Hedefin canı 
    float maxTargetHealth;   // Hedefin canı bar tasarımı içn

    void LoadPathFromGrid(const int points[][2], int count);
};
