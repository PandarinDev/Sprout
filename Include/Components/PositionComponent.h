#pragma once

#include "Component.h"

#include <string>

namespace sprout {

    class PositionComponent final : public Component {
    
    public:

        static const std::string UID;

        int x;
        int y;

        PositionComponent(int x, int y);

    };

}