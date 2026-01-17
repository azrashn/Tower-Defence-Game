#include "wave.h" // Dosya isminle uyumlu
#include <string>

WaveManager::WaveManager() {
    currentWaveIndex = 0;
    spawnTimer = 0.0f;
    waveDelayTimer = 0.0f;
    enemiesSpawnedSoFar = 0;
}

void WaveManager::Init() {
    // --- OYUN DENGESİ (Balancing) BURADA YAPILIR ---
    // { Goblin Sayısı, Orc Sayısı, Çıkış Hızı }
    waves.push_back({ 5,  0, 1.5f }); // 1. Dalga: 5 Goblin
    waves.push_back({ 3,  2, 2.0f }); // 2. Dalga: Karışık
    waves.push_back({ 0,  5, 2.5f }); // 3. Dalga: Orc Saldırısı
    waves.push_back({ 10, 5, 1.0f }); // 4. Dalga: Hızlı Akın
    waves.push_back({ 5, 10, 1.5f }); // 5. Dalga: Final Boss
}

void WaveManager::Update(std::vector<Enemy>& enemies, const std::vector<Vector2>& path) {

    if (currentWaveIndex >= waves.size()) return;

    WaveDef& currentWave = waves[currentWaveIndex];
    int totalEnemiesInWave = currentWave.goblinCount + currentWave.orcCount;

    // Dalga bitti mi?
    if (enemiesSpawnedSoFar >= totalEnemiesInWave) {
        if (enemies.empty()) { // Sahne temizlendi mi?
            waveDelayTimer += GetFrameTime();
            if (waveDelayTimer > 3.0f) { // 3 Saniye Mola
                currentWaveIndex++;
                enemiesSpawnedSoFar = 0;
                waveDelayTimer = 0.0f;
            }
        }
        return;
    }

    // Düşman Üretimi (Spawning)
    spawnTimer += GetFrameTime();

    if (spawnTimer >= currentWave.spawnInterval) {
        spawnTimer = 0.0f;

        EnemyType typeToSpawn;

        // Önce Goblinler, bitince Orclar gelsin
        if (enemiesSpawnedSoFar < currentWave.goblinCount) {
            typeToSpawn = GOBLIN;
        }
        else {
            typeToSpawn = ORC;
        }

        enemies.push_back(Enemy(typeToSpawn, path));
        enemiesSpawnedSoFar++;
    }
}

void WaveManager::Draw() {
    const char* text;
    if (currentWaveIndex >= waves.size()) text = "VICTORY!";
    else text = TextFormat("WAVE: %d / %d", currentWaveIndex + 1, waves.size());

    DrawText(text, 20, 80, 20, RED);
}

bool WaveManager::IsVictory() const {
    return currentWaveIndex >= waves.size();
}