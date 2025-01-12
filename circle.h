#include "vector2.h"
#include "raylib.h"

class Circle {
    private:
        vector2 position, velocity;
        int radius;
        double mass;
        Color color;
    
    public:
        Circle(vector2 position, vector2 velocity, int radius, Color color){
            this->position = position;
            this->velocity = velocity;
            this->radius = radius;
            this->color = color;
            this->mass = PI * radius * radius;
        }

        void Draw() {
            DrawCircle(position.x, position.y, radius, color);
        }
};