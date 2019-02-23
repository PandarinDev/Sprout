#pragma once

#include "Component.h"

#include <string>

namespace sprout {

    class DisplayComponent final : public Component {

    public:

        static const std::string UID;

        char representation;

        DisplayComponent(char representation);

    };

}