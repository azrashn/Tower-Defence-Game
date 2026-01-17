#pragma once
#include "raylib.h"
#include <vector>
#include "types.h"
#include "constants.h" 

class Map {
public:
    Map();
    ~Map();

    void Update();
    void Draw();

    void LoadLevel(int levelIndex);

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

    Texture2D texTowerSlot;

    float startX;
    float startY;
    float tileSize;

};