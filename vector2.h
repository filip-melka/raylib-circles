#include <cmath>
struct vector2 {
    double x, y;

    vector2 operator+(const vector2& other) const {
        return {x+other.x, y+other.y};
    }
    vector2 operator-(const vector2& other) const {
        return {x-other.x, y-other.y};
    }
    vector2 operator*(double scalar) const {
        return {x*scalar, y*scalar};
    }
    vector2 operator/(double scalar) const {
        return {x/scalar, y/scalar};
    }

    double dot(const vector2& other) const {
        return x*other.x + y*other.y;
    }
    double magnitude() const {
        return std::sqrt(x*x + y*y);
    }

    vector2 normalize() const {
        double mag = magnitude();
        if(mag == 0) return {0,0};
        return {x/mag, y/mag};
    }
};