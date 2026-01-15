#pragma once
#include "raylib.h"
#include <vector>
#include "types.h"

// Manages the game board layout
class Map{
public:
    Map();       // Sets up the grid
    void Draw(); // Renders the whole map

    void Update(); // Yeni güncelledim. Amaç Update işlemi için tanım yapmak.
    Tile* CheckTile(Vector2 mousePosition); // Seçilen tile koridnatı için tanım gerekiyordu
    
    //Yol kontrolü
    bool IsRoad(int gridX, int gridY) const;

    //Tile* GetTileAtPosition(Vector2 mousePos);

private:
    std::vector<std::vector<Tile>> grid; // 2D grid storage
    int rows;
    int cols;
    float tileSize; // Size of each block in pixels
    Texture2D backgroundTexture;
};