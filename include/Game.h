#pragma once
#include "Enemy.h"
#include "Maze.h"
#include "Player.h"
#include "raylib.h"

enum GameState { PLAYING, GAME_OVER };

class Game {
   private:
    Maze maze;
    Player player;
    Enemy enemy;
    Enemy enemy2;
    GameState state;

    int score;
    int scoreTimer;
    bool enemy2Active;

    bool foodActive;
    Cell foodCell;
    int foodTimer;
    int foodSpawnTimer;
    int nextFoodSpawnTime;

    void SpawnFood();

   public:
    Game();

    void Update();
    void Draw();
    void Restart();
};