#pragma once
#include <vector>
#include "raylib.h"
#include "Maze.h"
#include "Node.h"

class Enemy {
private:
    Cell cell;
    int moveTimer;
    std::vector<Cell> currentPath;

public:
    Enemy(Cell start);

    void Update(const Maze& maze, Cell playerCell);
    void Draw(const Maze& maze) const;
    void Reset(Cell start);
    Cell GetCell() const;
};
