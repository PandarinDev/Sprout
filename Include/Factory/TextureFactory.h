#pragma once

#include "Graphics/Texture.h"

#include <string>
#include <memory>

namespace sprout {

	class TextureFactory final {

	public:

		static std::unique_ptr<Texture> createFromFile(const std::string& filePath);

	private:

		TextureFactory() = default;

	};

}