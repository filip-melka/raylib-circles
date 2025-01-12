#include "raylib.h"
#include "stdlib.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "circle.h"
#include <iostream>

using namespace std;

const int screenWidth = 700;
const int screenHeight = 700;

vector2 getRandomNormalizedVector(){
    float x = (rand() % 2000 - 1000) / 1000.0f;
    float y = (rand() % 2000 - 1000) / 1000.0f;

    vector2 v {x,y};

    return v.normalize();
}

bool doesOverlap(Circle* newCircle, vector<Circle*> circles){
    for(Circle* circle : circles){
        double distance = (newCircle->getPosition()-circle->getPosition()).magnitude();
        if(distance <= newCircle->getRadius() + circle->getRadius()){
            return true;
        }
    }
    return false;
}

vector<Circle*> generateCircles(vector<int> radii, Color color, Circle* boundaries){
    vector<Circle*> circles;
    circles.reserve(radii.size());

    int index = 0;
    while(circles.size() < radii.size()){
        vector2 position;
        position.x = rand() % (boundaries->getRadius() - radii[index]) + radii[index];
        position.y = rand() % (boundaries->getRadius() - radii[index]) + radii[index];

        cout << position.x << " " << position.y << endl;

        if(position.magnitude() + radii[index] >= boundaries->getRadius()){
            continue;
        }

        Circle* newCircle = new Circle(position, getRandomNormalizedVector(), radii[index], color);

        if(!doesOverlap(newCircle, circles)){
            circles.push_back(newCircle);
            index++;
        }
    }

    return circles;
}

int main(void)
{
    srand(time(NULL));

    Circle* boundaries = new Circle(vector2 {screenWidth/2,screenHeight/2}, {0,0}, screenWidth/2.01, BLACK);

    vector<Circle*> circles = generateCircles(vector<int> {50}, WHITE, boundaries);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        boundaries->Draw();

        for(Circle* circle : circles){
            circle->Draw();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}