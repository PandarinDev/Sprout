#include "Components/DisplayComponent.h"

namespace sprout {

    const std::string DisplayComponent::UID = "DisplayComponent";

    DisplayComponent::DisplayComponent(
        char representation,
        const glm::vec3& color) :
        representation(representation),
        color(color) {}

}