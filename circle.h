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
            this->mass = PI * radius * radius;
            this->velocity = velocity * 15000/mass;
            this->radius = radius;
            this->color = color;
        }

        void Draw() {
            DrawCircle(position.x, position.y, radius, color);
        }

        void update() {
            position = position + velocity;
        }

        vector2 getPosition(){
            return position;
        }
        vector2 getVelocity(){
            return velocity;
        }
        int getRadius(){
            return radius;
        }

        void setVelocity(vector2 velocity){
            this->velocity = velocity;
        }
};