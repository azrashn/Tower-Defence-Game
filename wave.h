#pragma once
#include "raylib.h"
#include <vector>
#include "enemy.h"

// Bir dalganın kimlik kartı
struct WaveDef {
    int goblinCount;
    int orcCount;
    float spawnInterval; // Düşmanlar arası bekleme süresi
};

class WaveManager {
public:
    WaveManager();

    // Sesleri ve Wave verilerini yükler
    void Init();

    // Ana döngü: Düşman üretir, dalgayı takip eder
    void Update(std::vector<Enemy>& enemies, const std::vector<Vector2>& path);

    // Ekrana "Wave: 1/5" yazar
    void Draw();

    // Oyun bitti mi?
    bool IsVictory() const;

private:
    std::vector<WaveDef> waves;
    int currentWaveIndex;

    float spawnTimer;
    float waveDelayTimer;

    int enemiesSpawnedSoFar;
    
    bool isSpawning; 
};