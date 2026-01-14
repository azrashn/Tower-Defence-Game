#include "tower.h"
#include "raymath.h"

void Tower::Update(std::vector<Enemy>& enemies) {
    targetEnemy = nullptr;

    for (Enemy& e : enemies) {
        if (!e.active) continue;

        float d = Vector2Distance(position, e.position);
        if (d <= range) {
            targetEnemy = &e;
            break;
        }
    }
}

Tower::Tower(Vector2 pos, TowerType t) {
    position = pos;
    type = t;
    range = 120.0f;
}

void Tower::Draw() {
    Color c = GRAY;
    if (type == ARCHER_TOWER) c = BLUE;
    if (type == MAGE_TOWER)  c = PURPLE;

    DrawCircleLines(position.x, position.y, range, Fade(GRAY, 0.3f));
    DrawRectangle(position.x - 16, position.y - 16, 32, 32, c);

       if (targetEnemy) {
        DrawLineV(position, targetEnemy->position, RED);
    }
}
