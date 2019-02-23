#include "Components/DisplayComponent.h"

namespace sprout {

    const std::string DisplayComponent::UID = "DisplayComponent";

    DisplayComponent::DisplayComponent(char representation) :
        representation(representation) {}

}