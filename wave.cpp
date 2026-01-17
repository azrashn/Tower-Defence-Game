#include "wave.h" 
#include <string>

WaveManager::WaveManager() {
    currentWaveIndex = 0;
    spawnTimer = 0.0f;
    waveDelayTimer = 2.0f; // oyun başı hazırlık
    enemiesSpawnedSoFar = 0;
    isSpawning = false;
}

void WaveManager::Init() {
    // --- OYUN DENGESİ (Balancing) BURADA YAPILIR ---
    // { Goblin Sayısı, Orc Sayısı, Çıkış Hızı }
    waves.clear();

    waves.push_back({ 10,  2, 1.5f }); // 1. Dalga: 5 Goblin
    waves.push_back({ 12,  3, 1.5f }); // 2. Dalga: Karışık
    
    for (int i = 2; i < 5; i++) {
        int goblins = i * 5;
        int orcs = i + GetRandomValue(0, 5);

        float interval = 1.0f - (i * 0.05f);
        if (interval < 0.2f) interval = 0.2f;

        waves.push_back({ goblins, orcs, interval });
    }
}

void WaveManager::Update(std::vector<Enemy>& enemies, const std::vector<Vector2>& path) {

     if (IsVictory()) return;

    WaveDef& wave = waves[currentWaveIndex];
    int totalEnemies = wave.goblinCount + wave.orcCount;

    // Tüm düşmanlar spawnlandıysa
    if (!isSpawning) {
        waveDelayTimer -= GetFrameTime();
        if (waveDelayTimer <= 0.0f) {
            isSpawning = true;
            enemiesSpawnedSoFar = 0;
            spawnTimer = 0.0f;
        }
        return;
    }


    if (enemiesSpawnedSoFar >= totalEnemies) {
        if (enemies.empty()) {
            isSpawning = false;
            currentWaveIndex++;
            waveDelayTimer = 4.0f;
        }
        return;
    }

    // Düşman Üretimi (Spawning)
    spawnTimer += GetFrameTime();

    if (spawnTimer >= wave.spawnInterval) {
        spawnTimer = 0.0f;

        EnemyType type;

        // Önce Goblinler, bitince Orclar gelsin
        if (enemiesSpawnedSoFar < wave.goblinCount) {
            type = GOBLIN;
        }
        else {
            type = ORC;
        }

        enemies.push_back(Enemy(path, type));
        enemiesSpawnedSoFar++;
    }
}

void WaveManager::Draw() {
   if (IsVictory()) {
        DrawText("VICTORY!", (GetScreenWidth() - MeasureText("VICTORY!", 60)) / 2, 300, 60, GREEN);
        return;
    }
       DrawText(TextFormat("WAVE: %d / %d", currentWaveIndex + 1, (int)waves.size()), 20, 80, 20, RED);
    if (!isSpawning && waveDelayTimer > 0.0f) {

        // Sayacı metne çevir 
       const char* text = TextFormat("NEXT WAVE: %.1f", waveDelayTimer);
        // Yazının genişliğini ölç, ortalamak için
       int textW = MeasureText(text, 40);

       DrawText(text, (GetScreenWidth() - textW) / 2, 400, 40, RED);  //Ekranın  ortasına Kırmızı renkle yaz
    }
}
bool WaveManager::IsVictory() const {
    return currentWaveIndex >= waves.size();
}