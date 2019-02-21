#include "Graphics/Renderbuffer.h"

namespace sprout {

	Renderbuffer::Renderbuffer(GLuint handle) : handle(handle) {}

	Renderbuffer::~Renderbuffer() {
		glDeleteRenderbuffers(1, &handle);
	}

	GLuint Renderbuffer::getHandle() const {
		return handle;
	}

}