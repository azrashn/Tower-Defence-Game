#include "map.h"

Map::Map() {

}

void Map::Update() {

}

void Map::Draw() {

}

Tile* Map::CheckTile(Vector2 mousePosition){

    int x = mousePosition.x / tileSize;
    int y = mousePosition.y / tileSize;

    if (x < 0 || y < 0 || x >= cols || y >= rows)
        return nullptr;

    return &grid[y][x];
}