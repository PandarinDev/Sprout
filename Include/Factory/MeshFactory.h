#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/Geometry.h"
#include "Graphics/VertexAttribute.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include <string>
#include <memory>
#include <array>
#include <vector>

namespace sprout {

    class MeshFactory final {

    public:

		static std::unique_ptr<Mesh> loadGeometry(const Geometry& geometry, const std::vector<VertexAttribute>& attributes);

    private:

        MeshFactory() = default;

    };

}