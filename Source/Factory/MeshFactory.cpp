#include "Factory/MeshFactory.h"
#include "Utility/FileUtils.h"
#include "Utility/StringUtils.h"

#include <vector>
#include <sstream>
#include <stdexcept>

namespace sprout {

    std::unique_ptr<Mesh> MeshFactory::loadGeometry(const Geometry& geometry, const std::vector<VertexAttribute>& attributes) {
		GLuint vertexArrayObject, vertexBufferObject;
		glCreateVertexArrays(1, &vertexArrayObject);
		glCreateBuffers(1, &vertexBufferObject);
		glNamedBufferData(vertexBufferObject, geometry.size() * sizeof(float), geometry.data(), GL_STATIC_DRAW);
		unsigned totalStride = 0;
		for (const auto& attribute : attributes) totalStride += attribute.components * sizeof(float);
		glVertexArrayVertexBuffer(vertexArrayObject, 0, vertexBufferObject, 0, totalStride);
		// Enable and describe vertex array attributes
		unsigned stride = 0;
		unsigned vertexPerIndex = 0;
		for (const auto& attribute : attributes) {
		    glEnableVertexArrayAttrib(vertexArrayObject, attribute.index);
		    glVertexArrayAttribFormat(vertexArrayObject, attribute.index, attribute.components, GL_FLOAT, GL_FALSE, stride);
		    glVertexArrayAttribBinding(vertexArrayObject, attribute.index, 0);
		    stride += attribute.components * sizeof(float);
		    vertexPerIndex += attribute.components;
		}
		return std::make_unique<Mesh>(vertexArrayObject, vertexBufferObject, geometry.size() / vertexPerIndex);
    }

}