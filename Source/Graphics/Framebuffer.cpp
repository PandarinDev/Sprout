#include "Graphics/Framebuffer.h"

namespace sprout {

	Framebuffer::Framebuffer(
		GLuint handle,
		std::unordered_map<FramebufferTextureType, std::unique_ptr<Texture>>&& textures,
		std::unordered_map<FramebufferRenderbufferType, std::unique_ptr<Renderbuffer>>&& renderbuffers) :
		handle(handle), textures(std::move(textures)), renderbuffers(std::move(renderbuffers)) {}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &handle);
	}

	const Texture& Framebuffer::getTexture(FramebufferTexture type) const {
		return *textures.at(static_cast<FramebufferTextureType>(type));
	}

	GLuint Framebuffer::getHandle() const {
		return handle;
	}

}