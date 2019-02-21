#include "Graphics/Text.h"

namespace sprout {

	Text::Text(std::unique_ptr<Mesh> mesh, std::shared_ptr<Texture> texture) :
		mesh(std::move(mesh)), texture(texture) {}

	Mesh& Text::getMesh() const {
		return *mesh;
	}

	const Texture& Text::getTexture() const {
		return *texture;
	}

}