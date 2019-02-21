#pragma once

namespace sprout {

    class VertexAttribute final {

    public:

        unsigned index;
        unsigned components;

        VertexAttribute(unsigned index, unsigned components) :
            index(index), components(components) {}

    };

}