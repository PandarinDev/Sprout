#include "Scenes/DefaultScene.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>

namespace sprout {

    DefaultScene::DefaultScene(Renderer& renderer, InputManager& inputManager) : renderer(renderer) {
        textPtr = std::shared_ptr<Text>(renderer.getFont().generateText("Hello, world!").release());
        textPtr->applyTransformation(glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 250.0f, 0.0f)));
        for (int i = 0; i < textPtr->getNumberOfCharacters(); i += 2) {
            textPtr->setCharacterColor(i, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        auto& camera = renderer.getCamera();
    }

    void DefaultScene::tick(const Timer& timer) {
        float time = timer.getTime();
        for (int i = 0; i < textPtr->getNumberOfCharacters(); ++i) {
            float f = std::sin(time + i * 0.1);
            float shift = f * 100.0f;
            glm::mat4 transformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, shift, 0.0f));
            textPtr->applyCharacterTransformation(i, transformation);
        }
        renderer.render(textPtr);
    }

}