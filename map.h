#pragma once
#include "raylib.h"
#include <vector>

// Represents a single square on the grid
struct Tile
{
    Rectangle rect; // Position and size
    int id;         // Tile type (e.g., 0=Grass, 6=Road)
    Color color;    // Debug or visual color
};

// Manages the game board layout
class Map
{
public:
    Map();       // Sets up the grid
    void Draw(); // Renders the whole map

    void Update(); // Yeni güncelledim. Amaç Update işlemi için tanım yapmak.
    Tile* CheckTile(Vector2 mousePosition); // Seçilen tile koridnatı için tanım gerekiyordu

private:
    std::vector<std::vector<Tile>> grid; // 2D grid storage
    int rows;
    int cols;
    float tileSize; // Size of each block in pixels
};