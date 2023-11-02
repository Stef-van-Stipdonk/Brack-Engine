//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BUTTON_HPP
#define BRACK_ENGINE_BUTTON_HPP


#include "UIObject.hpp"

class Button : public UIObject {
public:
    Button() = default;

    ~Button() = default;

    bool IsInteractable() const;

    void SetInteractable(const bool interactable);

    //Callback moet nog toegevoegd worden
};


#endif //BRACK_ENGINE_BUTTON_HPP
