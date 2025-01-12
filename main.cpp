#include "raylib.h"
#include "stdlib.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include "circle.h"

using namespace std;

const int screenWidth = 700;
const int screenHeight = 700;

vector2 getRandomNormalizedVector(){
    float x = (rand() % 2000 - 1000) / 1000.0f;
    float y = (rand() % 2000 - 1000) / 1000.0f;

    vector2 v {x,y};

    return v.normalize();
}

int main(void)
{
    Circle* boundaries = new Circle(vector2 {screenWidth/2,screenHeight/2}, {0,0}, screenWidth/2.01, BLACK);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        boundaries->Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}