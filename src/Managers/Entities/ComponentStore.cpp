//
// Created by jesse on 17/11/2023.
//

#include "../../includes/ComponentStore.hpp"

ComponentStore ComponentStore::instance;

ComponentStore &ComponentStore::GetInstance() {
    return instance;
}

void ComponentStore::removeComponentsOfEntity(entity entityId) {
    if (entityToComponent.size() <= entityId)
        return;

    auto componentIds = entityToComponent[entityId];
    for (auto componentId: componentIds) {
        components[componentId].erase(entityId);
    }
}
