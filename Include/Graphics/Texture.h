#pragma once

#include "External/glad.h"

namespace sprout {

	class Texture final {

	public:

		Texture(GLuint handle, int width, int height);
		~Texture();
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void use(GLuint unit) const;

		GLuint getHandle() const;
		int getWidth() const;
		int getHeight() const;

	private:

		const GLuint handle;
		const int width;
		const int height;

	};

}