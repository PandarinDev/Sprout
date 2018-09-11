#pragma once

#include <GL/glew.h>

namespace winter {

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