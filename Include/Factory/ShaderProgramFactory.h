#pragma once

#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"

#include <vector>
#include <memory>

namespace sprout {

	class ShaderProgramFactory final {

	public:

		static std::unique_ptr<ShaderProgram> createDefaultProgram();
		static std::unique_ptr<ShaderProgram> createFromShaders(const std::vector<std::unique_ptr<Shader>>& shaders);

	private:

		// Default 2D program
		static constexpr const char* defaultVS = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"uniform mat4 u_ModelViewMatrix;\n"
			"layout (location = 0) in vec2 in_Position;\n"
			"layout (location = 1) in vec2 in_UV;\n"
			"layout (location = 2) in vec3 in_Color;\n"
			"out vec2 fs_UV;\n"
			"out vec3 fs_Color;\n"
			"void main() {\n"
				"fs_UV = in_UV;\n"
				"fs_Color = in_Color;\n"
				"gl_Position = u_ProjectionMatrix * u_ModelViewMatrix * vec4(in_Position, 0.0, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS = ""
			"#version 330 core\n"
			"uniform sampler2D u_TexUnit;\n"
			"in vec2 fs_UV;\n"
			"in vec3 fs_Color;\n"
			"layout (location = 0) out vec4 out_Color;\n"
			"void main() {\n"
			"out_Color = texture(u_TexUnit, fs_UV) * vec4(fs_Color, 1.0);"
			"}\n";

	};

}