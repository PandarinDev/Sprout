#pragma once

#include "External/glad.h"

namespace sprout {

	class Shader final {

	public:

		Shader(GLuint handle);
		~Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		GLuint getHandle() const;

	private:

		const GLuint handle;

	};

}