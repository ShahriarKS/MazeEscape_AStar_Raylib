# Maze Escape Game using A* Pathfinding

A 2D Raylib + C++ game where the player escapes a maze while an enemy uses A* pathfinding to chase the player.

## DSA Used
- 2D Grid / Matrix
- Graph traversal concept
- A* Search Algorithm
- Priority Queue
- Vector / Pair
- Collision with grid tiles

## Controls
- Arrow Keys / WASD: Move player
- R: Restart
- ESC: Exit

## Build

Use MSYS2 UCRT64 terminal inside this folder:

```bash
g++ src/*.cpp -o MazeEscape.exe -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm
cp /ucrt64/bin/libraylib.dll .
./MazeEscape.exe
```

## GitHub Suggested Title
Maze Escape Game using A* Pathfinding in C++ Raylib
