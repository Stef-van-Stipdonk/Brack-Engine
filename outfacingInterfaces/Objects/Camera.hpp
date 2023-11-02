//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERA_HPP
#define BRACK_ENGINE_CAMERA_HPP


#include "GameObject.hpp"
#include "Helpers/Color.hpp"
#include "Helpers/Vector2.hpp"

class Camera : public GameObject {
public:
    Color GetBackgroundColor() const;

    void SetBackgroundColor(const Color color);

    Vector2 GetSize() const;

    void SetSize(const Vector2 size);
};


#endif //BRACK_ENGINE_CAMERA_HPP
