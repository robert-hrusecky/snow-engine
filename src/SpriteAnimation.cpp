/*
 * SpriteAnimation.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: Robert
 */

#include "SpriteAnimation.h"

#include "VertexData.h"
namespace SnowEngine
{

SpriteAnimation::SpriteAnimation()
{
	// Empty
}

SpriteAnimation::SpriteAnimation(const glm::ivec4& rect, int num, int xNum, int fps, const GLTexture& texture) :
		m_rect(rect), m_num(num), m_xNum(xNum), m_fps(fps), m_texture(texture)
{
}

glm::vec4 SpriteAnimation::getUV() const
{
	glm::vec4 uv;
	uv.x = (float) ((m_frame % m_xNum) * m_rect.z + m_rect.x) / m_texture.width;
	uv.y = (float) ((m_frame / m_xNum) * m_rect.w + m_rect.y) / m_texture.height;
	uv.z = (float) m_rect.z / m_texture.width;
	uv.w = (float) m_rect.w / m_texture.height;
	return uv;
}

void SpriteAnimation::update(float deltaTime)
{
	update(deltaTime, m_fps);
}

void SpriteAnimation::update(float deltaTime, float fps)
{
	m_time += deltaTime;
	if (m_time >= 1.0f / fps) {
		m_frame++;
		m_frame %= m_num;
		m_time = 0;
	}
}

void SpriteAnimation::setFrame(int frame)
{
	m_frame = frame % m_num;
}

int SpriteAnimation::getFrame() const
{
	return m_frame;
}

const GLTexture& SpriteAnimation::getTexture() const
{
	return m_texture;
}

int SpriteAnimation::getWidth() const
{
	return m_rect.z;
}

int SpriteAnimation::getHeight() const
{
	return m_rect.w;
}

void SpriteAnimation::draw(SpriteBatch& spriteBatch, const glm::vec2& pos, bool flipped, float depth, float angle) const
{
	spriteBatch.draw(glm::vec4(pos, (flipped ? -1 : 1) * m_rect.z, m_rect.w), getUV(), m_texture.id, depth, angle);
}

} /* namespace SnowEngine */
