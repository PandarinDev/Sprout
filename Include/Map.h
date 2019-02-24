#pragma once

#include "Scene.h"
#include "Graphics/Renderer.h"
#include "Input/InputManager.h"
#include "Entities/Entity.h"
#include "Tile.h"

#include <vector>

namespace sprout {

    class Map final : public Scene {

    public:
    
        Map(int width, int height, Renderer& renderer, InputManager& inputManager);

        void tick(const Timer& timer) override;
        void addEntity(const std::shared_ptr<Entity>& entity);

        const Tile& getTileAt(int x, int y) const;        

    private:

        int width;
        int height;
        Renderer& renderer;
        InputManager& inputManager;
        std::vector<std::vector<Tile>> tiles;
        std::vector<std::shared_ptr<Entity>> entities;

    };

}