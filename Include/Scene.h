#pragma once

#include "Timer.h"

namespace sprout {

    class Scene {

    public:

        virtual ~Scene() = default;
        virtual void tick(const Timer& timer) = 0;

    };

}