#include "Entities/Player.h"

#include "Components/PositionComponent.h"
#include "Components/DisplayComponent.h"

namespace sprout {

    Player::Player() {
        addComponent(std::make_shared<PositionComponent>(0, 0));
        addComponent(std::make_shared<DisplayComponent>('@'));
    }

}