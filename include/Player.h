#pragma once
#include "raylib.h"
#include "Maze.h"
#include "Node.h"

class Player {
private:
    Cell cell;
    int moveTimer;

public:
    Player(Cell start);

    void Update(const Maze& maze);
    void Draw(const Maze& maze) const;
    void Reset(Cell start);
    Cell GetCell() const;
};
