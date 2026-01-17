#pragma once
#include "map.h"
#include "enemy.h"
#include <vector>
#include "raylib.h"
#include "tower.h"
#include "constants.h"
#include "wave.h" // <--- EKLENDİ: WaveManager dosyasını dahil ettik

class Game {
public:
    Game();
    void Update();
    void Draw();
    void Reset(); // Oyunu sıfırlama fonksiyonu

    bool gameOver; // Oyun durumu bitmiş mi onu bilip yazdırmak amaçlanıyor

private:
    Map map;

    // <--- EKLENDİ: Oyundaki dalga yönetimini yapacak ana nesne
    WaveManager waveManager;

    int gold; // Oyuncu parası 

    // Mapde tile seçimi için gereken tanımlamalar
    Tile* mouseTile;
    Tile* lastMouseTile;
    Tile* selectedTile;

    float mouseTime;

    std::vector<Enemy> enemies;
    std::vector<Tower> towers;

    // Düşmanların izleyeceği sabit rota
    std::vector<Vector2> levelPath;

    void LoadPathFromGrid(const int points[][2], int count);

    float targetHealth;      // Hedefin canı 
    float maxTargetHealth;   // Hedefin canı bar tasarımı için
};