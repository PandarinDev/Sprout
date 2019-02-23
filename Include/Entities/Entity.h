#pragma once

#include "Components/Component.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace sprout {

    class Entity {

    public:

        template<typename T>
        void addComponent(const std::shared_ptr<T>& component) {
            components.emplace(T::UID, component);
        }

        template<typename T>
        bool hasComponent() {
            return components.find(T::UID) != components.end();
        }

        template<typename T>
        std::shared_ptr<T> getComponent() {
            return std::static_pointer_cast<T>(components.find(T::UID)->second);
        }

    private:

        std::unordered_map<std::string, std::shared_ptr<Component>> components;

    };

}