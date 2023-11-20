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

    static void AddGameObject(GameObject *gameObject);

    static void AddCamera(Camera *camera);

    static GameObject GetGameObjectByName(const std::string &name);

    static std::vector<GameObject> GetGameObjectsByName(const std::string &name);

    static GameObject GetGameObjectByTag(const std::string &tag);

    static std::vector<GameObject> GetGameObjectsByTag(const std::string &tag);
    
    static void RemoveGameObject(GameObject &gameObject);
};


#endif //BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP
