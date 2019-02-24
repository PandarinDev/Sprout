#include "Input/MovementManager.h"
#include "Components/PositionComponent.h"

namespace sprout {

    MovementManager::MovementManager(
        const std::shared_ptr<Player>& player,
        const std::vector<std::vector<Tile>>& tiles) :
        player(player), tiles(tiles) {}

    void MovementManager::keyDown(KeyType key) {}

    void MovementManager::keyHeld(KeyType key) {}

    void MovementManager::keyUp(KeyType key) {
        auto position = player->getComponent<PositionComponent>();
        int xChange = 0;
        int yChange = 0;
        switch (key) {
            case GLFW_KEY_A:
                xChange = -1;
                break;
            case GLFW_KEY_D:
                xChange = 1;
                break;
            case GLFW_KEY_W:
                yChange = 1;
                break;
            case GLFW_KEY_S:
                yChange = -1;
                break;
        }
        // Prevent stepping out of boundaries
        if (
            position->x + xChange < 0 ||
            position->y + yChange < 0 ||
            position->x + xChange >= tiles.size() ||
            position->y + yChange >= tiles.at(position->x).size()) {
            return;
        }
        // Prevent stepping on non-walkable tiles
        if (tiles.at(position->x + xChange).at(position->y + yChange).isWalkable()) {
            position->x += xChange;
            position->y += yChange;
        }
    }

}