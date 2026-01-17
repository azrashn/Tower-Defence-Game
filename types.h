#pragma once
#include "raylib.h"

class Enemy;

enum TileType {
    BLOCKED = 0,    
    ROAD = 1,       
    BUILDABLE = 2,  
    TOWER = 3,      
    TARGET = 9      
};

// Kule Tipleri
enum TowerType {
    NONE = 0,       // Kule yok veya seçili değil
    ARCHER_TOWER,   // Okçu
    MAGE_TOWER,     // Büyücü
    CANNON_TOWER    // Topçu
};

enum EnemyType {
    GOBLIN, ORC, BOSS
};

struct Tile {
    Rectangle rect;
    TileType type;
    TowerType towerType;
    bool occupied;
    bool hasTree;
    Color color;
    int id;
};

struct Bullet {
    Vector2 position;
    Vector2 targetPos;    // Sabit hedef
    Enemy* lockedEnemy;   // Kilitlenen Düşman -> mermi takip edecedk

    float speed;
    float damage;
    bool active;
    TowerType type;
};
