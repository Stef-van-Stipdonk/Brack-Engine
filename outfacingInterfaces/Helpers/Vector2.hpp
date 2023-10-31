//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_VECTOR2_HPP
#define BRACK_ENGINE_VECTOR2_HPP

#include "cmath"

class Vector2 {
public:
    Vector2() : x(0.0f), y(0.0f) {};

    Vector2(const float x, const float y) : x(x), y(y) {};

    ~Vector2() = default;

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    void setX(const float newX);

    void setY(const float newY);

    [[nodiscard]] float magnitude() const;

    [[nodiscard]] Vector2 normalized() const;

    [[nodiscard]] float dot(const Vector2 &other) const;

    [[nodiscard]] float cross(const Vector2 &other) const;

    [[nodiscard]] float distance(const Vector2 &other) const;

    [[nodiscard]] float angel() const;

    Vector2 operator+(const Vector2 &other) const;

    Vector2 operator-(const Vector2 &other) const;

    Vector2 operator*(const float &other) const;

    Vector2 operator/(const float &other) const;

private:
    float x, y;
};


#endif //BRACK_ENGINE_VECTOR2_HPP
