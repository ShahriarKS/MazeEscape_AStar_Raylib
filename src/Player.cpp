#include "Player.h"

#include "Constants.h"

Player::Player(Cell start) {
    cell = start;
    moveTimer = 0;
}

void Player::Update(const Maze& maze) {
    moveTimer++;

    // Controls player movement speed
    if (moveTimer < PLAYER_MOVE_DELAY) return;

    int newRow = cell.row;
    int newCol = cell.col;

    // Keyboard movement input
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        newRow--;
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        newRow++;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        newCol--;
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        newCol++;
    else
        return;

    // Move only if target cell is not a wall
    if (!maze.IsWall(newRow, newCol)) {
        cell.row = newRow;
        cell.col = newCol;
        moveTimer = 0;
    }
}

void Player::Draw(const Maze& maze) const {
    Vector2 pos = maze.CellToPosition(cell);

    // Draw player body + eyes
    DrawCircle((int)pos.x, (int)pos.y, TILE_SIZE / 3, YELLOW);
    DrawCircle((int)pos.x - 6, (int)pos.y - 5, 3, BLACK);
    DrawCircle((int)pos.x + 6, (int)pos.y - 5, 3, BLACK);
}

void Player::Reset(Cell start) {
    cell = start;
    moveTimer = 0;
}

Cell Player::GetCell() const { return cell; }