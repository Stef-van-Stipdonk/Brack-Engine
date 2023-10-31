//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_COLOR_HPP
#define BRACK_ENGINE_COLOR_HPP

class Color {
public:
    Color() = default;

    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};

    ~Color() = default;

    float r;
    float g;
    float b;
    float a;
};

#endif //BRACK_ENGINE_COLOR_HPP
