#include "Map.h"
#include "Input/MovementManager.h"
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
        auto player = std::make_shared<Player>();
        inputManager.registerKeyEventListener(std::make_unique<MovementManager>(player, tiles));
        addEntity(player);
    }

    void Map::tick(const Timer& timer) {
        // Collect displayable entities
        std::unordered_map<
            std::pair<int, int>,
            std::shared_ptr<DisplayComponent>,
            PairHash> entityRepresentations;
        for (const auto& entity : entities) {
            if (entity->hasComponent<PositionComponent>() &&
                entity->hasComponent<DisplayComponent>()) {
                const auto& position = entity->getComponent<PositionComponent>();
                const auto& display = entity->getComponent<DisplayComponent>();
                entityRepresentations.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(position->x, position->y),
                    std::forward_as_tuple(display));
            }
        }
        // Combine tiles into a text
        std::string textStr;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char representation = getTileAt(x, y).getRepresentation();
                auto entityIt = entityRepresentations.find(std::make_pair(x, y));
                if (entityIt != entityRepresentations.end()) {
                    const auto& display = entityIt->second;
                    representation = display->representation;
                }
                textStr += representation;
            }
            textStr += '\n';
        }
        std::shared_ptr<Text> text = renderer.getFont().generateText(textStr);
        // Assign color values
        for (const auto& entity : entityRepresentations) {
            int x = entity.first.first;
            int y = entity.first.second;
            glm::vec3 color = entity.second->color;
            text->setCharacterColor(y * width + x, color);
        }
        renderer.render(text);
    }

    void Map::addEntity(const std::shared_ptr<Entity>& entity) {
        entities.emplace_back(entity);
    }

    const Tile& Map::getTileAt(int x, int y) const {
        return tiles.at(x).at(y);
    }

}