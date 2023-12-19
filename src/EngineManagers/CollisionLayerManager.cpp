//
// Created by jesse on 19/12/2023.
//

#include "../../outfacingInterfaces/EngineManagers/CollisionLayerManager.hpp"
#include "../Logger.hpp"

CollisionLayerManager CollisionLayerManager::instance;

CollisionLayerManager &CollisionLayerManager::getInstance() {
    return instance;
}

CollisionLayerManager::CollisionLayerManager() : nextCategory(1) {}

void CollisionLayerManager::defineCollision(const std::string &name) {
    CollisionCategory newCategory = nextCategory;
    nextCategory <<= 1;

    if (nextCategory == 0) {
        Logger::Error("Too many collision categories defined");
    }

    collisionCategories[name] = newCategory;
}

CollisionCategory CollisionLayerManager::getCategory(const std::string &name) {
    auto item = collisionCategories.find(name);
    if (item != collisionCategories.end()) {
        return item->second;
    }

    CollisionCategory newCategory = nextCategory;
    nextCategory <<= 1;

    if (nextCategory == 0) {
        Logger::Error("Too many collision categories defined");
    }

    collisionCategories[name] = newCategory;
    return newCategory;
}

void CollisionLayerManager::defineMask(const std::string &name, const std::vector<std::string> &categories) {
    CollisionMask mask = 0;
    for (auto &categoryName: categories) {
        auto it = collisionCategories.find(categoryName);
        if (it != collisionCategories.end()) {
            mask |= it->second;
        } else {
            Logger::Error("Category not found: " + categoryName);
        }
    }

    collisionMasks[name] = mask;
}

CollisionMask CollisionLayerManager::getMask(const std::string &name) {
    auto item = collisionMasks.find(name);
    if (item != collisionMasks.end()) {
        return item->second;
    }

    Logger::Error("Mask not found: " + name);
    return 0;
}
