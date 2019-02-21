#pragma once

#include <glm/vec2.hpp>

namespace sprout {

    class Camera final {

    public:

        Camera(const glm::vec2& position = { 0.0f, 0.0f });

        void translate(const glm::vec2& translation);
        void rotate(float degrees);
        void zoom(float percent);

        const glm::vec2& getPosition() const;
        float getRotationDegrees() const;
        float getZoom() const;

        void setPosition(const glm::vec2& position);
        void setRotationDegrees(float rotationDeg);
        void setZoom(float zoomPercent);

    private:
    
        glm::vec2 position;
        float rotationDeg;
        float zoomPercent;

    };

}