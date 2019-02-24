#include "Entities/Player.h"

#include "Components/PositionComponent.h"
#include "Components/DisplayComponent.h"

namespace sprout {

    static const glm::vec3 RED(1.0f, 0.0f, 0.0f);

    Player::Player() {
        addComponent(std::make_shared<PositionComponent>(0, 0));
        addComponent(std::make_shared<DisplayComponent>('@', RED));
    }

}