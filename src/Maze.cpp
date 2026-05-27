#include "Maze.h"

// Maze constructor
// Initializes the maze layout from a temporary 2D array
Maze::Maze()
{

    // 1 = Wall
    // 0 = Empty path
    // 2 = Exit cell (currently unused in Draw())
    int temp[ROWS][COLS] = {

        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    // Copy temp layout into main grid
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            grid[r][c] = temp[r][c];
        }
    }
}

// Draw the maze on screen
void Maze::Draw() const
{

    for (int r = 0; r < ROWS; r++)
    {

        for (int c = 0; c < COLS; c++)
        {

            // Convert grid coordinates to screen coordinates
            int x = OFFSET_X + c * TILE_SIZE;
            int y = OFFSET_Y + r * TILE_SIZE;

            // Draw wall cells
            if (grid[r][c] == 1)
            {

                DrawRectangle(
                    x,
                    y,
                    TILE_SIZE,
                    TILE_SIZE,
                    DARKBLUE);

                DrawRectangleLines(
                    x,
                    y,
                    TILE_SIZE,
                    TILE_SIZE,
                    BLUE);
            }

            // Draw empty path cells
            else
            {

                DrawRectangle(
                    x,
                    y,
                    TILE_SIZE,
                    TILE_SIZE,
                    Color{25, 25, 35, 255});

                DrawRectangleLines(
                    x,
                    y,
                    TILE_SIZE,
                    TILE_SIZE,
                    Color{45, 45, 60, 255});
            }
        }
    }
}

// Checks whether a cell is a wall
bool Maze::IsWall(int row, int col) const
{

    // Outside maze treated as wall
    if (!IsInside(row, col))
        return true;

    return grid[row][col] == 1;
}

// Boundary checker
bool Maze::IsInside(int row, int col) const
{

    return row >= 0 &&
           row < ROWS &&
           col >= 0 &&
           col < COLS;
}

// Exit checker
// Currently disabled
bool Maze::IsExit(Cell cell) const
{

    return false;
}

// Converts grid cell -> pixel position
Vector2 Maze::CellToPosition(Cell cell) const
{

    return {
        (float)(OFFSET_X +
                cell.col * TILE_SIZE +
                TILE_SIZE / 2),

        (float)(OFFSET_Y +
                cell.row * TILE_SIZE +
                TILE_SIZE / 2)};
}

// Converts pixel position -> grid cell
Cell Maze::PositionToCell(Vector2 pos) const
{

    return {
        (int)((pos.y - OFFSET_Y) / TILE_SIZE),
        (int)((pos.x - OFFSET_X) / TILE_SIZE)};
}

// Player spawn location
Cell Maze::GetPlayerStart() const
{

    return {1, 1};
}

// Enemy spawn location
Cell Maze::GetEnemyStart() const
{

    return {13, 1};
}

// Maze exit location
Cell Maze::GetExitCell() const
{

    return {13, 18};
}