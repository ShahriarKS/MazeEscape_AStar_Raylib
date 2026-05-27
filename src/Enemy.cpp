#include "Enemy.h"

#include "AStar.h"
#include "Constants.h"

Enemy::Enemy(Cell start) {
    cell = start;
    moveTimer = 0;
}

void Enemy::Update(const Maze& maze, Cell playerCell) {
    moveTimer++;

    // Enemy moves only after a small delay
    if (moveTimer < ENEMY_MOVE_DELAY) return;

    // Use A* to calculate shortest path toward player
    currentPath = AStar::FindPath(maze, cell, playerCell);

    if (!currentPath.empty()) {
        cell = currentPath[0];
    }

    moveTimer = 0;
}

void Enemy::Draw(const Maze& maze) const {
    Vector2 pos = maze.CellToPosition(cell);

    // Visualize predicted A* route
    for (size_t i = 0; i < currentPath.size(); i++) {
        Vector2 p = maze.CellToPosition(currentPath[i]);
        DrawCircle((int)p.x, (int)p.y, 5, Color{255, 0, 0, 100});
    }

    DrawCircle((int)pos.x, (int)pos.y, TILE_SIZE / 3, RED);

    // Enemy face styling
    DrawCircle((int)pos.x - 6, (int)pos.y - 5, 3, WHITE);
    DrawCircle((int)pos.x + 6, (int)pos.y - 5, 3, WHITE);
}

void Enemy::Reset(Cell start) {
    cell = start;
    moveTimer = 0;
    currentPath.clear();
}

Cell Enemy::GetCell() const { return cell; }