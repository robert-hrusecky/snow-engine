/*
 * SpriteFont.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: Robert
 */

#include "SpriteFont.h"

#include <fstream>

#include "gferrors.h"
#include "ResourceManager.h"
#include "GLTexture.h"

namespace SnowEngine
{

const int NUM_FONT_ROWS = 6;
const int NUM_FONT_COLS = 16;

SpriteFont::SpriteFont(std::string fontPath) :
		m_padding(0)
{
	// Get or load the font sprite sheet
	GLTexture* texture = ResourceManager::getTexture(fontPath + ".png");
	m_texture = texture->id;

	// Find the font size by using the texture size
	m_resolution = texture->width / 16;

	std::ifstream specFile(fontPath + ".fspec");

	if (specFile.fail())
	{
		fatalError("Failed to load font spec for font: " + fontPath);
	}

	const float CHARS_HEIGHT = (float) NUM_FONT_ROWS * m_resolution;
	const float CHARS_WIDTH = (float) NUM_FONT_COLS * m_resolution;
	const float LAST_ROW_Y = (float) CHARS_HEIGHT - m_resolution; ///< Y value of the last row of chars in the sprite sheet
	const float TEX_WIDTH = (float) texture->width;
	const float TEX_HEIGHT = (float) texture->height;

	// Calcuate the UV rects of each char
	int count = 0;
	int charWidth;
	for (float y = 0.0f; y < LAST_ROW_Y; y += m_resolution)
	{
		for (float x = 0.0f; x < CHARS_WIDTH; x += m_resolution)
		{
			specFile >> charWidth;
			m_glyphDims[count] = glm::vec2(charWidth, m_resolution);
			m_uvRects[count] = glm::vec4(x / TEX_WIDTH, y / TEX_HEIGHT, charWidth / TEX_WIDTH, m_resolution / TEX_HEIGHT);
			count++;
		}
	}

	for (float x = 0.0f; x < CHARS_WIDTH - m_resolution; x += m_resolution)
	{
		specFile >> charWidth;
		m_glyphDims[count] = glm::vec2(charWidth, m_resolution);
		m_uvRects[count] = glm::vec4(x / TEX_WIDTH, LAST_ROW_Y / TEX_HEIGHT, charWidth / TEX_WIDTH, m_resolution / TEX_HEIGHT);
		count++;
	}

	specFile >> m_padding;

	specFile.close();
}

SpriteFont::~SpriteFont()
{
}

void SpriteFont::draw(const std::string& str, float x, float y, const ColorRGBA8& color, SpriteBatch& batch, float scale, float depth)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		unsigned char charIndex;
		if (str[i] < FIRST_CHAR || str[i] > LAST_CHAR)
		{
			charIndex = '?' - FIRST_CHAR;
		}
		else
		{
			charIndex = (unsigned char) str[i] - FIRST_CHAR;
		}
		batch.draw(glm::vec4(x, y, m_glyphDims[charIndex] * scale), m_uvRects[charIndex], m_texture, depth, 0.0f, color);
		x += (m_glyphDims[charIndex].x + m_padding) * scale;
	}
}

float SpriteFont::calculateWidth(const std::string& str, float scale)
{
	float width = 0.0f;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		unsigned char charIndex;
		if (str[i] < FIRST_CHAR || str[i] > LAST_CHAR)
		{
			charIndex = '?' - FIRST_CHAR;
		}
		else
		{
			charIndex = (unsigned char) str[i] - FIRST_CHAR;
		}
		width += (m_glyphDims[charIndex].x + m_padding) * scale;
	}
	return width;
}

} /* namespace SnowEngine */
