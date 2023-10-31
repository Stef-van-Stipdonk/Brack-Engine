//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_UIOBJECT_HPP
#define BRACK_ENGINE_UIOBJECT_HPP


#include "GameObject.hpp"
#include "Helpers/Vector2.hpp"

class UIObject : public GameObject {
public:
    UIObject() = default;

    virtual ~UIObject() = default;

    Vector2 GetSize() const;

    void SetSize(const Vector2 size);
};


#endif //BRACK_ENGINE_UIOBJECT_HPP
