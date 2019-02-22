#pragma once

#include "Graphics/Texture.h"

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <vector>
#include <memory>
#include <unordered_map>

namespace sprout {

	class Text final {

	public:

		static constexpr int VERTICES_PER_CHARACTER = 42;

		Text(std::vector<float>&& vertices, std::shared_ptr<Texture> texture);

		void applyTransformation(const glm::mat4& transformation);
		void applyCharacterTransformation(int i, const glm::mat4& transformation);

		std::vector<float> getVertices() const;
		const Texture& getTexture() const;
		const glm::mat4& getTransformations() const;
		int getNumberOfCharacters() const;

		void setColor(const glm::vec3& color);
		void setCharacterColor(int i, const glm::vec3& color);

	private:

		std::vector<float> vertices;
		std::shared_ptr<Texture> texture;
		glm::mat4 transformations;
		std::unordered_map<int, glm::mat4> transformationsPerCharacter;

	};

}