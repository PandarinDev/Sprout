#include "Map.h"
#include "Components/PositionComponent.h"
#include "Components/DisplayComponent.h"
#include "Entities/Player.h"
#include "Utility/PairHash.h"

#include <memory>

namespace sprout {

    Map::Map(int width, int height, Renderer& renderer, InputManager& inputManager) :
        width(width), height(height), renderer(renderer), inputManager(inputManager) {
        tiles.reserve(width);
        for (int x = 0; x < width; ++x) {
            std::vector<Tile> rows;
            rows.reserve(height);
            for (int y = 0; y < height; ++y) {
                // For now every tile is a dot and walkable
                rows.emplace_back(Tile('#', true));
            }
            tiles.emplace_back(std::move(rows));
        }
        addEntity(std::make_unique<Player>());
    }

    void Map::tick(const Timer& timer) {
        // Collect displayable entities
        std::unordered_map<std::pair<int, int>, char, PairHash> entityRepresentations;
        for (const auto& entity : entities) {
            if (entity->hasComponent<PositionComponent>() &&
                entity->hasComponent<DisplayComponent>()) {
                const auto& position = entity->getComponent<PositionComponent>();
                char representation = entity->getComponent<DisplayComponent>()->representation;
                entityRepresentations.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(position->x, position->y),
                    std::forward_as_tuple(representation));
            }
        }
        // Combine tiles into a text
        std::string textStr;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char representation = getTileAt(x, y).getRepresentation();
                auto entityIt = entityRepresentations.find(std::make_pair(x, y));
                if (entityIt != entityRepresentations.end()) {
                    representation = entityIt->second;
                }
                textStr += representation;
            }
            textStr += '\n';
        }
        std::shared_ptr<Text> text = renderer.getFont().generateText(textStr);
        renderer.render(text);
    }

    void Map::addEntity(std::unique_ptr<Entity> entity) {
        entities.emplace_back(std::move(entity));
    }

    const Tile& Map::getTileAt(int x, int y) const {
        return tiles.at(x).at(y);
    }

}