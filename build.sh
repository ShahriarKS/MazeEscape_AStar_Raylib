#!/usr/bin/env bash
g++ src/*.cpp -o MazeEscape.exe -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm
cp /ucrt64/bin/libraylib.dll .
./MazeEscape.exe
