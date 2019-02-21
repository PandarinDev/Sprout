#pragma once

#include "Graphics/Shader.h"
#include "Graphics/ShaderType.h"

#include <string>
#include <memory>

namespace sprout {

	class ShaderFactory final {

	public:

		static std::unique_ptr<Shader> createFromSource(ShaderType type, const std::string& source);

	private:

		ShaderFactory() = default;

	};

}