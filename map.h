#pragma once
#include "raylib.h"
#include <vector>
#include "types.h"
#include "constants.h" 

// Manages the game board layout
class Map{
public:
    Map();       // Sets up the grid
    ~Map();

    void Draw(); // Renders the whole map
    void Update(); // Yeni güncelledim. Amaç Update işlemi için tanım yapmak.

    int GetWidth() const { return currentGridW; }
    int GetHeight() const { return currentGridH; }

    Tile* CheckTile(Vector2 position);
    
    Rectangle townHallRect;

    

private:
   std::vector<std::vector<Tile>> grid;

    int currentGridW;
    int currentGridH;

    Texture2D texBackground;
    Texture2D texTarget;
    Texture2D texWall;
    Texture2D texTree;
    Texture2D texRoad;

    float startX;
    float startY;
    float tileSize;
};