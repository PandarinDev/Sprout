#include "Graphics/Renderer.h"
#include "Graphics/Quad.h"
#include "Utility/OGLUtils.h"
#include "External/glad.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <stdexcept>

namespace sprout {

	constexpr const char* Renderer::PROJECTION_MATRIX_UNIFORM;
	constexpr const char* Renderer::MODELVIEW_MATRIX_UNIFORM;

	Renderer::Renderer(
		const glm::vec3& clearColor,
		std::unique_ptr<ShaderProgram> shader,
		std::unique_ptr<Font> font,
		std::unique_ptr<Framebuffer> gBuffer,
		std::unique_ptr<Texture> defaultTexture,
		float fieldOfView,
		float perspectiveWidth,
		float perspectiveHeight,
		float perspectiveNear,
		float perspectiveFar) :
			projectionMatrix(glm::ortho(0.0f, perspectiveWidth, 0.0f, perspectiveHeight)),
			modelViewMatrix(glm::mat4(1.0f)) {
		configureDefaults();
		setClearColor(clearColor);
		setShaderProgram(std::move(shader));
		setFont(std::move(font));
	}

	void Renderer::beginFrame() {
		clearBuffers();
	}

	void Renderer::endFrame() {
		shader->use();
		projectionMatrixLocation = shader->getUniformLocation(PROJECTION_MATRIX_UNIFORM);
		modelViewMatrixLocation = shader->getUniformLocation(MODELVIEW_MATRIX_UNIFORM);
		for (const auto& text : textBuffer) {
			glBindVertexArray(text->getMesh().getVertexArrayObject());
			text->getTexture().use(0);
			shader->uploadMatrix(projectionMatrixLocation, projectionMatrix);
			shader->uploadMatrix(modelViewMatrixLocation, text->getMesh().getTransformations());
			glDrawArrays(GL_TRIANGLES, 0, text->getMesh().getNumberOfIndices());
		}
		textBuffer.clear();
		checkForErrors();
	}

	void Renderer::clearBuffers() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::render(const std::shared_ptr<Text>& text) {
		textBuffer.emplace_back(text);
	}

	Camera& Renderer::getCamera() {
		return camera;
	}

	const ShaderProgram& Renderer::getShaderProgram() const {
		return *shader;
	}

	const Font& Renderer::getFont() const {
		return *font;
	}

	void Renderer::setClearColor(const glm::vec3& clearColor) {
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	}

	void Renderer::setShaderProgram(std::unique_ptr<ShaderProgram> shader) {
		this->shader = std::move(shader);
	}

	void Renderer::setFont(std::unique_ptr<Font> font) {
        this->font = std::move(font);
	}

	void Renderer::configureDefaults() const {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::checkForErrors() const {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string errorMessage = OGLUtils::translateErrorCode(error);
			throw std::runtime_error("Rendering API error: " + errorMessage);
		}
	}

}