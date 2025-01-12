#include "raylib.h"
#include "stdlib.h"
#include <cmath>
#include <cstdlib>

using namespace std;

const int screenWidth = 700;
const int screenHeight = 500;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // DRAW

        EndDrawing();
    }

    CloseWindow();

    return 0;
}