//
// Created by jesse on 04/11/2023.
//

#ifndef BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP
#define BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP


#include <cstdint>
#include <optional>
#include "Objects/Camera.hpp"

class GameObjectConverter {
public:
    static Camera getMainCamera(uint32_t entityID);

    static GameObject getGameObject(uint32_t entityID);

    static void addGameObject(GameObject *gameObject);

    static void addCamera(Camera *camera);

    static std::optional<GameObject> getGameObjectByName(const std::string &name);

    static std::vector<GameObject> getGameObjectsByName(const std::string &name);

    static std::optional<GameObject> getGameObjectByTag(const std::string &tag);

    static std::vector<GameObject> getGameObjectsByTag(const std::string &tag);

    static void removeGameObject(GameObject &gameObject);
};


#endif //BRACK_ENGINE_GAMEOBJECTCONVERTER_HPP
