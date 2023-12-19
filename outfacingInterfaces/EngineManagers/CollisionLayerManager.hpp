//
// Created by jesse on 19/12/2023.
//

#ifndef BRACKOCALYPSE_COLLISIONLAYERMANAGER_HPP
#define BRACKOCALYPSE_COLLISIONLAYERMANAGER_HPP

#include <map>
#include <string>
#include <vector>
#include "../CollisionCategory.hpp"
#include "../CollisionMask.hpp"

class CollisionLayerManager {
public:
    static CollisionLayerManager &getInstance();

    void defineCollision(const std::string &name);

    CollisionCategory getCategory(const std::string &name);

    void defineMask(const std::string &name, const std::vector<std::string> &categories);

    CollisionMask getMask(const std::string &name);

private:

    static CollisionLayerManager instance;

    CollisionLayerManager();

    std::map<std::string, CollisionCategory> collisionCategories;
    std::map<std::string, CollisionMask> collisionMasks;

    CollisionCategory nextCategory;
};


#endif //BRACKOCALYPSE_COLLISIONLAYERMANAGER_HPP
