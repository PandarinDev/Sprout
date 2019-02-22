#include "Graphics/Text.h"

namespace sprout {

	constexpr int Text::VERTICES_PER_CHARACTER;

	Text::Text(std::vector<float>&& vertices, std::shared_ptr<Texture> texture) :
		vertices(std::move(vertices)), texture(texture), transformations(1.0f) {}

	void Text::applyTransformation(const glm::mat4& transformation) {
		this->transformations = transformation * this->transformations;
	}

	void Text::applyCharacterTransformation(int i, const glm::mat4& transformation) {
		transformationsPerCharacter[i] = transformation;
	}

	std::vector<float> Text::getVertices() const {
		std::vector<float> result(vertices);
		// Apply global transformations
		for (int i = 0; i < result.size(); i += 7) {
			glm::vec4 coordinate(vertices[i], vertices[i + 1], 0.0f, 1.0f);
			glm::vec2 transformed = transformations * coordinate;
			result[i] = transformed.x;
			result[i + 1] = transformed.y;
		}
		// Apply per-character transformations
		for (const auto& entry : transformationsPerCharacter) {
			int index = entry.first;
			const auto& transformation = entry.second;
			int startingIndex = index * VERTICES_PER_CHARACTER;
			int endingIndex = (index + 1) * VERTICES_PER_CHARACTER;
			for (int i = startingIndex; i < endingIndex; i += 7) {
				glm::vec4 coordinate(result[i], result[i + 1], 0.0f, 1.0f);
				glm::vec2 transformed = transformation * coordinate;
				result[i] = transformed.x;
				result[i + 1] = transformed.y;
			}
		}

		return result;
	}	

	const Texture& Text::getTexture() const {
		return *texture;
	}

	const glm::mat4& Text::getTransformations() const {
		return transformations;
	}

	int Text::getNumberOfCharacters() const {
		return vertices.size() / VERTICES_PER_CHARACTER;
	}

	void Text::setColor(const glm::vec3& color) {
		int numberOfCharacters = getNumberOfCharacters();
		for (int i = 0; i < numberOfCharacters; ++i) {
			setCharacterColor(i, color);
		}
	}

	void Text::setCharacterColor(int i, const glm::vec3& color) {
		int bufferOffset = i * VERTICES_PER_CHARACTER;
		for (int j = 0; j < 6; ++j) {
			int vertexOffset = bufferOffset + (j * 7);
			vertices[vertexOffset + 4] = color.x;
			vertices[vertexOffset + 5] = color.y;
			vertices[vertexOffset + 6] = color.z;
		}
	}

}