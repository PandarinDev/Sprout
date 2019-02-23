#include "Components/PositionComponent.h"

namespace sprout {

    const std::string PositionComponent::UID = "PositionComponent";

    PositionComponent::PositionComponent(int x, int y) : x(x), y(y) {}

}