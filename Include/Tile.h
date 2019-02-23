#pragma once

namespace sprout {

    class Tile final {

    public:

        Tile(char representation, bool walkable);

        char getRepresentation() const;
        bool isWalkable() const;

    private:

        char representation;
        bool walkable;

    };

}