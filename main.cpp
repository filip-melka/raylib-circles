#include "raylib.h"
#include "stdlib.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "circle.h"
#include <iostream>

using namespace std;

const int screenWidth = 1000;
const int screenHeight = 1000;
vector2 center {screenWidth/2, screenHeight/2};

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
        position.x = rand() % (screenWidth- radii[index]) + radii[index];
        position.y = rand() % (screenHeight - radii[index]) + radii[index];

        cout << position.x << " " << position.y << endl;

        if((center - position).magnitude()  + radii[index] >= boundaries->getRadius()){
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

void checkBoundariesCollision(vector<Circle*> circles, Circle* boundaries){
    for(Circle* circle : circles){
        if((center - circle->getPosition()).magnitude()  + circle->getRadius() >= boundaries->getRadius()){
            vector2 n = (circle->getPosition() - boundaries->getPosition()).normalize();
            double dotProduct = circle->getVelocity().dot(n);

            circle->setVelocity(circle->getVelocity() - n * (2 * dotProduct));
        }
    }
}

void updateAfterCollisionVelocity(Circle* circleA, Circle* circleB){
    vector2 rABn = (circleB->getPosition() - circleA->getPosition()).normalize(); // nHat
    vector2 vAB = circleB->getVelocity() - circleA->getVelocity();
    double vABn = vAB.dot(rABn);

    if(vABn >= 0) return;

    double impulse = (2 * vABn) / (circleA->getMass() + circleB->getMass());

    circleA->setVelocity(circleA->getVelocity() + rABn * (impulse * circleB->getMass()));
    circleB->setVelocity(circleB->getVelocity() - rABn * (impulse * circleA->getMass()));
}

void checkCollisions(vector<Circle*> circles){
    for(int a=0; a<circles.size(); a++){
        for (int b=a+1; b<circles.size(); b++) {
            if((circles[b]->getPosition()-circles[a]->getPosition()).magnitude() <= circles[a]->getRadius() + circles[b]->getRadius()){
                updateAfterCollisionVelocity(circles[a], circles[b]);
            }
        }
    }
}

int main(void)
{
    srand(time(NULL));

    Circle* boundaries = new Circle(vector2 {screenWidth/2,screenHeight/2}, {0,0}, screenWidth/2.01, BLACK);

    vector<Circle*> circles = generateCircles(vector<int> {60, 80, 140, 200}, WHITE, boundaries);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        boundaries->Draw();

        for(Circle* circle : circles){
            circle->Draw();
            circle->update();
        }

        checkCollisions(circles);
        checkBoundariesCollision(circles, boundaries);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}