#include "AStar.h"

#include <algorithm>
#include <cmath>
#include <queue>

struct AStarNode {
    Cell cell;
    int gCost;
    int hCost;
    int fCost;

    bool operator>(const AStarNode& other) const { return fCost > other.fCost; }
};

// Manhattan distance heuristic for grid movement
static int Heuristic(Cell a, Cell b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

std::vector<Cell> AStar::FindPath(const Maze& maze, Cell start, Cell goal) {
    std::priority_queue<AStarNode, std::vector<AStarNode>,
                        std::greater<AStarNode>>
        openSet;

    bool visited[ROWS][COLS] = {};
    int gCost[ROWS][COLS];
    Cell parent[ROWS][COLS];

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            gCost[r][c] = 1000000;
            parent[r][c] = {-1, -1};
        }
    }

    // Start node begins with zero movement cost
    gCost[start.row][start.col] = 0;
    openSet.push({start, 0, Heuristic(start, goal), Heuristic(start, goal)});

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!openSet.empty()) {
        AStarNode current = openSet.top();
        openSet.pop();

        Cell cur = current.cell;

        if (visited[cur.row][cur.col]) continue;
        visited[cur.row][cur.col] = true;

        // Rebuild path after reaching the target cell
        if (cur == goal) {
            std::vector<Cell> path;
            Cell step = goal;

            while (step != start) {
                path.push_back(step);
                step = parent[step.row][step.col];

                if (step.row == -1 || step.col == -1) {
                    return {};
                }
            }

            std::reverse(path.begin(), path.end());
            return path;
        }

        // Check four-directional movement: up, down, left, right
        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i];
            int nc = cur.col + dc[i];

            if (!maze.IsInside(nr, nc)) continue;
            if (maze.IsWall(nr, nc)) continue;
            if (visited[nr][nc]) continue;

            int newG = gCost[cur.row][cur.col] + 1;

            if (newG < gCost[nr][nc]) {
                gCost[nr][nc] = newG;
                parent[nr][nc] = cur;

                Cell next = {nr, nc};
                int h = Heuristic(next, goal);
                int f = newG + h;

                openSet.push({next, newG, h, f});
            }
        }
    }

    return {};
}