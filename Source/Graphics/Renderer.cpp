#include "Graphics/Renderer.h"
#include "Graphics/VertexAttribute.h"
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
		configureBuffers();
		configureDefaults();
		setClearColor(clearColor);
		setShaderProgram(std::move(shader));
		setFont(std::move(font));
	}

	void Renderer::beginFrame() {
		clearBuffers();
	}

	void Renderer::endFrame() {
		static constexpr auto componentsPerVertex = 7;
		projectionMatrixLocation = shader->getUniformLocation(PROJECTION_MATRIX_UNIFORM);
		modelViewMatrixLocation = shader->getUniformLocation(MODELVIEW_MATRIX_UNIFORM);
		shader->use();
		shader->uploadMatrix(projectionMatrixLocation, projectionMatrix);
		shader->uploadMatrix(modelViewMatrixLocation, glm::mat4(1.0f));
		// Count the number of total vertices
		std::size_t totalVertices = 0;
		for (const auto& text : textBuffer) {
			totalVertices += text->getVertices().size();
		}
		std::vector<float> vertexBuffer;
		vertexBuffer.reserve(totalVertices);
		// Concatenate vertex buffers
		glBindVertexArray(vertexArrayObject);
		for (const auto& text : textBuffer) {
			text->getTexture().use(0);
			const auto& vertices = text->getVertices();
			vertexBuffer.insert(vertexBuffer.end(), vertices.begin(), vertices.end());
		}
		// Upload and draw
		glNamedBufferData(vertexBufferObject, vertexBuffer.size() * sizeof(float), vertexBuffer.data(), GL_STREAM_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.size() / componentsPerVertex);
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

	void Renderer::configureBuffers() {
		static const std::vector<VertexAttribute> attributes = {
			{ 0, 2 }, // Coordinates
			{ 1, 2 }, // Texture coordinates
			{ 2, 3 }  // Colors
		};

		glCreateVertexArrays(1, &vertexArrayObject);
		glCreateBuffers(1, &vertexBufferObject);
		unsigned totalStride = 0;
		for (const auto& attribute : attributes) totalStride += attribute.components * sizeof(float);
		glVertexArrayVertexBuffer(vertexArrayObject, 0, vertexBufferObject, 0, totalStride);
		// Enable and describe vertex array attributes
		unsigned stride = 0;
		for (const auto& attribute : attributes) {
		    glEnableVertexArrayAttrib(vertexArrayObject, attribute.index);
		    glVertexArrayAttribFormat(vertexArrayObject, attribute.index, attribute.components, GL_FLOAT, GL_FALSE, stride);
		    glVertexArrayAttribBinding(vertexArrayObject, attribute.index, 0);
		    stride += attribute.components * sizeof(float);
		}
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