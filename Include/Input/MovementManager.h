#pragma once

#include "Input/InputManager.h"
#include "Entities/Player.h"
#include "Tile.h"

#include <vector>
#include <memory>
#include <unordered_set>

namespace sprout {

    class MovementManager final : public KeyEventListener {

    public:

        MovementManager(
            const std::shared_ptr<Player>& player,
            const std::vector<std::vector<Tile>>& tiles);

        void keyDown(KeyType key) override;
        void keyHeld(KeyType key) override;
        void keyUp(KeyType key) override;

    private:

        std::shared_ptr<Player> player;
        const std::vector<std::vector<Tile>>& tiles;

    };

}