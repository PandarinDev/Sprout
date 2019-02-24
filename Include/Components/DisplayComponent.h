#pragma once

#include "Component.h"

#include <glm/vec3.hpp>

#include <string>

namespace sprout {

    class DisplayComponent final : public Component {

    public:

        static const std::string UID;

        char representation;
        glm::vec3 color;

        DisplayComponent(
            char representation,
            const glm::vec3& color);

    };

}