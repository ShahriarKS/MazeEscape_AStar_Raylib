#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Node.h"

class Maze {
private:
    int grid[ROWS][COLS];

public:
    Maze();

    void Draw() const;
    bool IsWall(int row, int col) const;
    bool IsInside(int row, int col) const;
    bool IsExit(Cell cell) const;

    Vector2 CellToPosition(Cell cell) const;
    Cell PositionToCell(Vector2 pos) const;

    Cell GetPlayerStart() const;
    Cell GetEnemyStart() const;
    Cell GetExitCell() const;
};
