#include "Input/InputManager.h"
#include "Utility/TypeUtils.h"
#include "Engine.h"

#include <algorithm>

namespace sprout {

    InputManager::InputManager() :
        mousePosition(0.0f, 0.0f),
        lastMousePosition(0.0f, 0.0f),
        mouseCoordinated(false) {
        glfwSetJoystickCallback(joystickCallback);
        discoverJoysticks();
    }

	const glm::vec2& InputManager::getMousePosition() const {
		return mousePosition;
	}

    void InputManager::tick() {
		static const auto keyDownValue = TypeUtils::enumValue(KeyEvent::KEY_DOWN);
        static const auto keyUpValue = TypeUtils::enumValue(KeyEvent::KEY_UP);
        // Handle keyboard events
		for (const auto& listener : keyListeners) {
            // Handle key-down events
            for (const auto& key : keysDown) {
                listener->keyDown(key);
            }
            // Handle key-held events
            for (const auto& key : keysHeld) {
                listener->keyHeld(key);
            }
            // Handle key-up events
            for (const auto& key : keysUp) {
                listener->keyUp(key);
            }
        }
        keysHeld.insert(keysDown.begin(), keysDown.end());
        keysDown.clear();
        keysUp.clear();

		// Handle mouse events
		for (const auto& listener : mouseListeners) {
			listener->handleMouseEvent(mousePosition, lastMousePosition);
		}
		lastMousePosition = mousePosition;

        // Handle joystick events
        for (const auto& joystickEntry : joysticks) {
            // TODO
        }
    }

    void InputManager::hookInto(const Window& window) {
        window.setKeyCallback(keyCallback);
		window.setMouseCallback(mouseCallback);
    }

    void InputManager::registerKeyEventListener(std::unique_ptr<KeyEventListener> eventListener) {
        keyListeners.emplace_back(std::move(eventListener));
    }

	void InputManager::registerMouseEventListener(std::unique_ptr<MouseEventListener> eventListener) {
		mouseListeners.emplace_back(std::move(eventListener));
	}

    void InputManager::registerJoystickEventListener(std::unique_ptr<JoystickEventListener> eventListener) {
        joystickListeners.emplace_back(std::move(eventListener));
    }

    void InputManager::discoverJoysticks() {
        joysticks.clear();
        for (int id = GLFW_JOYSTICK_1; id <= GLFW_JOYSTICK_LAST; ++id) {
            if (glfwJoystickPresent(id)) {
                joysticks.emplace(id, std::make_unique<Joystick>(id, glfwGetJoystickName(id)));
            }
        }
    }

    void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto& instance = Engine::getInstance().getInputManager();
        switch (action) {
        case GLFW_PRESS:
            instance.keysDown.emplace(key);
            break;
        case GLFW_RELEASE:
            instance.keysDown.erase(key);
            instance.keysHeld.erase(key);
            instance.keysUp.emplace(key);
            break;
        }
    }

	void InputManager::mouseCallback(GLFWwindow* window, double x, double y) {
		auto& instance = Engine::getInstance().getInputManager();
        if (!instance.mouseCoordinated) {
            instance.mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));
            instance.mouseCoordinated = true;
        }
		instance.lastMousePosition = instance.mousePosition;
		instance.mousePosition.x = static_cast<float>(x);
		instance.mousePosition.y = static_cast<float>(y);
	}

    void InputManager::joystickCallback(int joy, int event) {
        auto& instance = Engine::getInstance().getInputManager();
        instance.discoverJoysticks();
    }

}