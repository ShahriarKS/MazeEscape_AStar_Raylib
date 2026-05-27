#include "Game.h"

#include <cstdlib>
#include <ctime>

Game::Game()
    : maze(),
      player(maze.GetPlayerStart()),
      enemy(maze.GetEnemyStart()),
      enemy2(Cell{1, 18}) {
    state = PLAYING;
    score = 0;
    scoreTimer = 0;
    enemy2Active = false;

    foodActive = false;
    foodTimer = 0;
    foodSpawnTimer = 0;
    nextFoodSpawnTime = 180;

    srand(time(0));
}

void Game::SpawnFood() {
    int row, col;

    do {
        row = rand() % ROWS;
        col = rand() % COLS;
    } while (maze.IsWall(row, col) || Cell{row, col} == player.GetCell() ||
             Cell{row, col} == enemy.GetCell());

    foodCell = {row, col};
    foodActive = true;
    foodTimer = 0;
}

void Game::Update() {
    if (IsKeyPressed(KEY_R)) {
        Restart();
    }

    if (state != PLAYING) return;

    player.Update(maze);
    enemy.Update(maze, player.GetCell());

    if (score >= 500) {
        enemy2Active = true;
    }

    if (enemy2Active) {
        enemy2.Update(maze, player.GetCell());
    }

    if (player.GetCell() == enemy.GetCell()) {
        state = GAME_OVER;
    }

    if (enemy2Active && player.GetCell() == enemy2.GetCell()) {
        state = GAME_OVER;
    }

    if (enemy2Active && enemy.GetCell() == enemy2.GetCell()) {
        score += 500;
        enemy2.Reset(Cell{1, 18});
    }

    scoreTimer++;
    if (scoreTimer >= 60) {
        score += 10;
        scoreTimer = 0;
    }

    // Random food spawn timing
    if (!foodActive) {
        foodSpawnTimer++;

        if (foodSpawnTimer >= nextFoodSpawnTime) {
            SpawnFood();
            foodSpawnTimer = 0;
            nextFoodSpawnTime = 120 + rand() % 241;
        }
    }

    // Food lasts for around 4 seconds
    if (foodActive) {
        foodTimer++;

        if (player.GetCell() == foodCell) {
            score += 250;
            foodActive = false;
            foodTimer = 0;
        }

        if (foodTimer >= 240) {
            foodActive = false;
            foodTimer = 0;
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Maze Survival using A* Pathfinding", 50, 20, 28, RAYWHITE);
    DrawText("Move: Arrow/WASD | Restart: R | Food: +250", 50, 50, 18, GRAY);
    DrawText(TextFormat("Score: %d", score), 680, 20, 28, YELLOW);

    maze.Draw();

    if (foodActive) {
        Vector2 foodPos = maze.CellToPosition(foodCell);
        DrawCircle((int)foodPos.x, (int)foodPos.y, TILE_SIZE / 4, ORANGE);
        DrawCircle((int)foodPos.x - 4, (int)foodPos.y - 4, 3, GOLD);
    }

    enemy.Draw(maze);

    if (enemy2Active) {
        enemy2.Draw(maze);
    }

    player.Draw(maze);

    if (state == GAME_OVER) {
        DrawRectangle(190, 260, 520, 140, Color{0, 0, 0, 210});
        DrawText("GAME OVER", 315, 285, 45, RED);
        DrawText(TextFormat("Final Score: %d", score), 335, 335, 24, YELLOW);
        DrawText("The A* enemy caught you! Press R to restart.", 245, 365, 20,
                 RAYWHITE);
    }

    EndDrawing();
}

void Game::Restart() {
    player.Reset(maze.GetPlayerStart());
    enemy.Reset(maze.GetEnemyStart());
    enemy2.Reset(Cell{1, 18});

    state = PLAYING;
    score = 0;
    scoreTimer = 0;
    enemy2Active = false;

    foodActive = false;
    foodTimer = 0;
    foodSpawnTimer = 0;
    nextFoodSpawnTime = 180;
}