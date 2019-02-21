#pragma once

#include "External/glad.h"

namespace sprout {

	enum class ShaderType : GLenum {
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

}