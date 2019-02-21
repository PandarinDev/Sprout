#pragma once

namespace sprout {

    class Scene {

    public:

        virtual ~Scene() = default;
        virtual void tick() = 0;

    };

}