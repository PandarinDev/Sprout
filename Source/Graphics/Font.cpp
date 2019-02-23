#include "Graphics/Font.h"

namespace sprout {

    Font::Font(const std::string &name, short size, unsigned short lineHeight, unsigned short base,
               std::unique_ptr<Texture> texture,
               std::unordered_map<FontChar::Id, FontChar>&& characters,
               std::unordered_map<std::pair<FontChar::Id, FontChar::Id>, short>&& kernings) :
               name(name), size(size), lineHeight(lineHeight), base(base), texture(texture.release()),
               characters(std::move(characters)), kernings(std::move(kernings)) {}

	std::unique_ptr<Text> Font::generateText(const std::string& content) const {
		std::vector<float> vertexBuffer(content.size() * Text::VERTICES_PER_CHARACTER);
		std::size_t counter = 0;
		float cursorX = 0.0f, cursorY = 0.0f;
		float textureWidth = texture->getWidth();
		float textureHeight = texture->getHeight();
		FontChar::Id lastChar = -1u;
		for (const auto c : content) {
			// Handle new-line characters
			if (c == '\n') {
				cursorX = 0.0f;
				cursorY += lineHeight;
				lastChar = -1u;
				continue;
			}
            const auto& fontChar = getFontChar(c);
			float x = cursorX + fontChar.xOffset;
			float y = cursorY;

			// Bottom right triangle
			vertexBuffer[counter++] = x;
			vertexBuffer[counter++] = y;
			vertexBuffer[counter++] = fontChar.x / textureWidth;
			vertexBuffer[counter++] = 1.0f - ((fontChar.y + fontChar.height) / textureHeight);
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;

			vertexBuffer[counter++] = x + fontChar.width;
			vertexBuffer[counter++] = y;
			vertexBuffer[counter++] = (fontChar.x + fontChar.width) / textureWidth;
			vertexBuffer[counter++] = 1.0f - ((fontChar.y + fontChar.height) / textureHeight);
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;

			vertexBuffer[counter++] = x + fontChar.width;
			vertexBuffer[counter++] = y + fontChar.height;
			vertexBuffer[counter++] = (fontChar.x + fontChar.width) / textureWidth;
			vertexBuffer[counter++] = 1.0f - (fontChar.y / textureHeight);
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			// Upper left triangle
			vertexBuffer[counter++] = x;
			vertexBuffer[counter++] = y;
			vertexBuffer[counter++] = fontChar.x / textureWidth;
			vertexBuffer[counter++] = 1.0f - ((fontChar.y + fontChar.height) / textureHeight);
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;

			vertexBuffer[counter++] = x + fontChar.width;
			vertexBuffer[counter++] = y + fontChar.height;
			vertexBuffer[counter++] = (fontChar.x + fontChar.width) / textureWidth;
			vertexBuffer[counter++] = 1.0f - (fontChar.y / textureHeight);
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;

			vertexBuffer[counter++] = x;
			vertexBuffer[counter++] = y + fontChar.height;
			vertexBuffer[counter++] = fontChar.x / textureWidth;
			vertexBuffer[counter++] = 1.0f - (fontChar.y / textureHeight);
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;
			vertexBuffer[counter++] = 1.0f;

            cursorX += fontChar.xAdvance;
			auto kerningIt = kernings.find(std::make_pair(lastChar, fontChar.id));
			if (kerningIt != kernings.end()) {
				cursorX += kerningIt->second;
			}
			lastChar = fontChar.id;
		}

        return std::make_unique<Text>(std::move(vertexBuffer), texture);
	}

    const std::string& Font::getName() const {
        return name;
    }

    short Font::getSize() const {
        return size;
    }

    unsigned short Font::getLineHeight() const {
        return lineHeight;
    }

    unsigned short Font::getBase() const {
        return base;
    }

    const Texture& Font::getTexture() const {
        return *texture;
    }

    const FontChar& Font::getFontChar(FontChar::Id id) const {
        return characters.at(id);
    }

    short Font::getKerningForPair(FontChar::Id first, FontChar::Id second) const {
        return kernings.at(std::make_pair(first, second));
    }

}