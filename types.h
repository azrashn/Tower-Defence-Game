#pragma once
#include "raylib.h"

class Enemy;

enum class TileType // state -> type dönüştürdüm. map.h kısmı buraya gelicek
{
    BLOCKED = 0,    // Duvar, Ağaç, Boşluk, SAHTE YOL (Düşman geçemez)
    ROAD = 1,       // Düşmanın yürüdüğü GERÇEK yol
    BUILDABLE = 2,  // Kule koyulabilir alan
    TOWER = 3,      // Üzerinde kule var
    TARGET = 9      // Pizza (Hedef)
};

enum EnemyType {
    GOBLIN,
    ORC, 
    BOSS
};

enum TowerType {
    NONE = 0,       // Kule yok veya seçili değil
    ARCHER_TOWER,   // Okçu
    MAGE_TOWER,     // Büyücü
    CANNON_TOWER    // Topçu
};

struct Tile
{
    Rectangle rect; // ekranın kapladığı alanı temsil ediyor
    TileType type;
 
    // Genel tanımlamalar. map.h kısmı
    bool occupied;
    Color color;
    int id;

    // x ve y tile'ı yapıp harita kordinat için tanımlandı
    int gridX;
    int gridY;
};
