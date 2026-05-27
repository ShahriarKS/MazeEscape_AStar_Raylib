#pragma once
#include <vector>
#include "Node.h"
#include "Maze.h"

class AStar {
public:
    static std::vector<Cell> FindPath(const Maze& maze, Cell start, Cell goal);
};
