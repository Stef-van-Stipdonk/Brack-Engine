//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_INPUTMANAGER_HPP
#define BRACK_ENGINE_INPUTMANAGER_HPP

#include <map>
#include <memory>
#include "Helpers/Vector2.hpp"
#include "Helpers/InputState.hpp"
#include "../../src/includes/EntityManager.hpp"

class InputManager {
public:
    InputManager() = default;

    ~InputManager() = default;

    void Initialize(std::shared_ptr<EntityManager> newEntityManager);

    void SetKeyPressed(const int key);

    void SetKeyReleased(const int key);

    bool IsKeyPressed(const int key) const;

    bool IsKeyClicked(const int key) const;

    bool IsKeyReleased(const int key) const;

    void SetMousePressed(const int key);

    void SetMouseReleased(const int key);

    bool IsMousePressed(const int key) const;

    bool IsMouseClicked(const int key) const;

    bool IsMouseReleased(const int key) const;

    void SetMousePosition(const Vector2 &position);

    Vector2 &GetMousePosition() const;

private:
    std::map<int, InputState> keyInputs;
    std::map<int, InputState> mouseInputs;
    std::unique_ptr<Vector2> mousePosition;
    std::shared_ptr<EntityManager> entityManager;
};


#endif //BRACK_ENGINE_INPUTMANAGER_HPP
