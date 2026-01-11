#pragma once
#include "raylib.h"

enum class TileType // state -> type dönüştürdüm. map.h kısmı buraya gelicek
{
    Empty,
    Blocked,
    Selected
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
