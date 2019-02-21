#include "Scenes/DefaultScene.h"
#include "Factory/MeshFactory.h"

namespace sprout {

    DefaultScene::DefaultScene(Renderer& renderer, InputManager& inputManager) : renderer(renderer) {
        textPtr = std::shared_ptr<Text>(renderer.getFont().generateText("Hello, world!").release());
		textPtr->getMesh().translate(glm::vec3(100.0f, 300.0f, 0.0f));
        auto& camera = renderer.getCamera();
    }

    void DefaultScene::tick() {
        renderer.render(textPtr);
    }

}