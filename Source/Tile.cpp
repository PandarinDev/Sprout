#include "Tile.h"

namespace sprout {

    Tile::Tile(char representation, bool walkable) :
        representation(representation), walkable(walkable) {}

    char Tile::getRepresentation() const {
        return representation;
    }

    bool Tile::isWalkable() const {
        return walkable;
    }

}