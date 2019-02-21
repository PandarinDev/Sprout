#include "Graphics/Camera.h"

namespace sprout {

    Camera::Camera(const glm::vec2& position) :
        position(position), rotationDeg(0.0f), zoomPercent(1.0f) {}

    void Camera::translate(const glm::vec2& translation) {
        position += translation;
    }

    void Camera::rotate(float degrees) {
        rotationDeg += degrees;
    }

    void Camera::zoom(float percent) {
        zoomPercent += percent;
    }

    const glm::vec2& Camera::getPosition() const {
        return position;
    }

    float Camera::getRotationDegrees() const {
        return rotationDeg;
    }

    float Camera::getZoom() const {
        return zoomPercent;
    }

    void Camera::setPosition(const glm::vec2& position) {
        this->position = position;
    }

    void Camera::setRotationDegrees(float rotationDeg) {
        this->rotationDeg = rotationDeg;
    }

    void Camera::setZoom(float zoomPercent) {
        this->zoomPercent = zoomPercent;
    }

}