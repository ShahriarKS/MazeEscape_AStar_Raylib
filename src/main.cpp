#include "raylib.h"
#include "Game.h"
#include "Constants.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Escape - A* Pathfinding");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}
