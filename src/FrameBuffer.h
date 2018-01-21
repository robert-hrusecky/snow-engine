/*
 * FrameBuffer.h
 *
 *  Created on: Aug 1, 2017
 *      Author: robert
 */

#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "SpriteBatch.h"
namespace SnowEngine
{

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	virtual ~FrameBuffer();
	void begin();
	void end();
	void draw(SpriteBatch& spriteBatch, const glm::vec4& rect);
	GLint getTexture();
private:
	GLuint m_texture = 0;
	GLuint m_fbo = 0;
	GLsizei m_screenWidth, m_screenHeight;
	GLsizei m_width, m_height;
};

}
