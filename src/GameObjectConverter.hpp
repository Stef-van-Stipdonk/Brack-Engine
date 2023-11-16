//
// Created by jesse on 04/11/2023.
//

#ifndef BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP
#define BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP


#include <cstdint>
#include "Objects/Camera.hpp"

class GameObjectConverter {
public:
    static Camera GetMainCamera(uint32_t entityID);

    static GameObject GetGameObject(uint32_t entityID);

    static void AddGameObject(GameObject* gameObject);

    static void AddCamera(std::unique_ptr<Camera> camera);

    static void RemoveGameObject(GameObject &gameObject);
};


#endif //BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP
