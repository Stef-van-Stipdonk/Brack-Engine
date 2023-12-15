//
// Created by jesse on 07/12/2023.
//

#ifndef BRACKOCALYPSE_TILEMAPCOMPONENT_HPP
#define BRACKOCALYPSE_TILEMAPCOMPONENT_HPP

#include <string>
#include <memory>
#include <vector>
#include <Components/Archetypes/RenderArchetype.hpp>
#include <Helpers/Vector2.hpp>

struct TileMapComponent : public RenderArchetype {
    explicit TileMapComponent() : RenderArchetype() {}

    ~TileMapComponent() override {

    };

    std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<TileMapComponent>(*this);
    }

    TileMapComponent(const TileMapComponent &other) : RenderArchetype(other) {
        tileMapPath = other.tileMapPath;
        tileSize = std::make_unique<Vector2>(*other.tileSize);
        tileMap = std::vector<std::vector<std::unique_ptr<Vector2>>>();
        for (const auto &row: other.tileMap) {
            auto newRow = std::vector<std::unique_ptr<Vector2>>();
            for (const auto &tile: row) {
                if (tile == nullptr) {
                    newRow.emplace_back(nullptr);
                    continue;
                }
                newRow.emplace_back(std::make_unique<Vector2>(*tile));
            }
            tileMap.emplace_back(std::move(newRow));
        }
        margin = other.margin;
    }

    std::string tileMapPath = "";
    std::unique_ptr<Vector2> tileSize = std::make_unique<Vector2>(0, 0);
    std::vector<std::vector<std::unique_ptr<Vector2>>> tileMap;
    int margin = 0;
};

#endif //BRACKOCALYPSE_TILEMAPCOMPONENT_HPP
