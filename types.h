#pragma once
#include "raylib.h"

enum class TileState
{
    Empty,
    Blocked,
    Selected
};

struct Tile
{
    Rectangle rect; // ekranın kapladığı alanı temsil ediyor
    TileState state;

    // x ve y tile'ı yapıp harita kordinat için tanımlandı
    int gridX;
    int gridY;
};
