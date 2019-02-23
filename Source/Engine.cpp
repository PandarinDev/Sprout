#include "Engine.h"

#include "Factory/ShaderProgramFactory.h"
#include "Factory/FontFactory.h"
#include "Factory/TextureFactory.h"
#include "Factory/FramebufferFactory.h"
#include "Map.h"

#include <glm/glm.hpp>

namespace sprout {

    Engine& Engine::getInstance() {
        static Engine instance;
        return instance;
    }

    void Engine::init(const Configuration& config) {
        initGLFW();
        window = std::make_unique<Window>(
            config.windowTitle,
            config.windowWidth,
            config.windowHeight,
            config.windowVSync,
            config.windowFullScreen);
        timer = std::make_unique<Timer>();
        inputManager = std::make_unique<InputManager>();
        inputManager->hookInto(*window);
        initGLAD();
        renderer = std::make_unique<Renderer>(
            glm::vec3(0.0f, 0.0f, 0.0f),
            ShaderProgramFactory::createDefaultProgram(),
            FontFactory::createFromFile("Assets/Fonts/ShareTech/sharetech.fnt"),
            FramebufferFactory::createGBuffer(config.windowWidth, config.windowHeight),
            TextureFactory::createFromFile("Assets/Textures/Default.png"),
		    glm::radians(config.rendererFieldOfView),
		    config.windowWidth,
            config.windowHeight,
            config.rendererDrawClose,
            config.rendererDrawDistance);
        scene = std::make_unique<Map>(20, 20, getRenderer());
    }

    void Engine::start() {
        while (!window->shouldClose()) {
            window->pollEvents();
            timer->tick();
            inputManager->tick();
            // Render and swap buffers
            renderer->beginFrame();
            scene->tick(*timer);
            renderer->endFrame();
            window->swapBuffers();
        }
    }

    Window& Engine::getWindow() const {
        return *window;
    }

    InputManager& Engine::getInputManager() const {
        return *inputManager;
    }

    Renderer& Engine::getRenderer() const {
        return *renderer;
    }

    Scene& Engine::getScene() const {
        return *scene;
    }

    void Engine::setScene(std::unique_ptr<Scene> scene) {
        this->scene = std::move(scene);
    }

    void Engine::initGLFW() {
        if (!glfwInit()) {
		    throw std::runtime_error("Failed to initialize GLFW.");
	    }
    }

    void Engine::initGLAD() {
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

}