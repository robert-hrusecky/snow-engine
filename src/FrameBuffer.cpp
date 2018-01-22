/*
 * FrameBuffer.cpp
 *
 *  Created on: Aug 1, 2017
 *      Author: robert
 */

#include "FrameBuffer.h"

#include "errors.h"
#include "ImageLoader.h"
namespace SnowEngine
{

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height) :
		m_width(width), m_height(height)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	ImageLoader::createTexture(&m_texture, m_width, m_height, nullptr);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		fatalError("Could not initialize fbo");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, &viewport[0]);
	m_screenWidth = viewport[2];
	m_screenHeight = viewport[3];
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo);
	glDeleteTextures(1, &m_texture);
}

void FrameBuffer::begin()
{
	glBindTexture(GL_TEXTURE_2D, 0); //To make sure the texture isn't bound
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_width, m_height);
}

void FrameBuffer::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_screenWidth, m_screenHeight);
}

GLint FrameBuffer::getTexture()
{
	return m_texture;
}

void FrameBuffer::draw(SpriteBatch& spriteBatch, const glm::vec4& rect)
{
	spriteBatch.draw(rect, glm::vec4(0.0f, 0.0f, 1.0f, -1.0f), m_texture, 0, 0.0f, SnowEngine::ColorRGBA8());
}

}
