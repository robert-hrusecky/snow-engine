/*
 * SpriteAnimation.h
 *
 *  Created on: Jan 23, 2017
 *      Author: Robert
 */

#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GLTexture.h"
#include "SpriteBatch.h"

namespace SnowEngine
{

class SpriteAnimation
{
public:
	SpriteAnimation();
	SpriteAnimation(const glm::ivec4& rect, int num, int xNum, int fps, const GLTexture& texture);
	glm::vec4 getUV() const;
	void update(float deltaTime);
	void update(float deltaTime, float fps);
	void setFrame(int frame);
	int getFrame() const;
	const GLTexture& getTexture() const;
	int getWidth() const;
	int getHeight() const;
	void draw(SpriteBatch& spriteBatch, const glm::vec2& pos, bool flipped = false, float depth = 0.0f, float angle = 0.0f) const;
private:
	glm::ivec4 m_rect;
	int m_num = 0;
	int m_xNum = 0;
	int m_fps = 0;
	int m_frame = 0;
	float m_time = 0.0f;
	GLTexture m_texture;
};

} /* namespace SnowEngine */
