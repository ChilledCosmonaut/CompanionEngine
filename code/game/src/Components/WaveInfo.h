#pragma once

class WaveInfo {
public:
    float waveCounter = 0.f;
    float enemiesAlive = 0.f;
    float baseEnemyCount = 1.0f;
};

class NewWave {};

struct Restock {};