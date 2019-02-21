#pragma once

#include "Scene.h"
#include "Graphics/Renderer.h"
#include "Input/InputManager.h"

#include <memory>

namespace sprout {

    class DefaultScene final : public Scene {

    public:

        DefaultScene(Renderer& renderer, InputManager& inputManager);

        void tick() override;

    private:

        Renderer& renderer;
        std::shared_ptr<Text> textPtr;

    };

}