/*
 * SpriteFont.h
 *
 *  Created on: Jul 24, 2015
 *      Author: Robert
 */

#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "SpriteBatch.h"

namespace SnowEngine
{

const unsigned char FIRST_CHAR = ' '; ///< 32
const unsigned char LAST_CHAR = '~'; ///< 126
const int NUM_FONT_CHARS = LAST_CHAR - FIRST_CHAR + 1;

class SpriteFont
{
public:
	SpriteFont(std::string fontPath);
	~SpriteFont();
	void draw(const std::string& str, float x, float y, const ColorRGBA8& color, SpriteBatch& batch, float scale = 1.0f, float depth = 0.0f);
	float calculateWidth(const std::string& str, float scale);
private:
	GLuint m_texture;
	int m_resolution, m_padding;
	glm::vec2 m_glyphDims[NUM_FONT_CHARS];
	glm::vec4 m_uvRects[NUM_FONT_CHARS];
};

} /* namespace SnowEngine */
