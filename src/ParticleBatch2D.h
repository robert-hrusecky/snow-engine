/*
 * ParticleBatch2D.h
 *
 *  Created on: Jul 31, 2015
 *      Author: Robert
 */

#pragma once

#include <glm/glm.hpp>
#include <functional>

#include "GLTexture.h"
#include "SpriteBatch.h"
#include "VertexData.h"

namespace SnowEngine
{

struct Particle2D
{
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 velocity = glm::vec2(0.0f);
	ColorRGBA8 color;
	float life = 0.0f;
	float width;
};

extern void defaultParticleUpdate(Particle2D& particle, float deltaTime);

class ParticleBatch2D
{
public:
	ParticleBatch2D();
	~ParticleBatch2D();

	void init(int maxParticles, float decayRate, const GLTexture& texture, std::function<void(Particle2D&, float)> updateFunc = defaultParticleUpdate);

	void addParticle(const glm::vec2& position, const glm::vec2& velocity, const ColorRGBA8& color, float width);
	void update(float deltaTime);
	void draw(SpriteBatch* spriteBatch);
private:
	int findFreeParticle();
	float m_decayRate = 0.01f;
	Particle2D* m_particles = nullptr;
	int m_maxParticles = 0;
	int m_lastFreeParticle = 0;
	GLTexture m_texture;
	std::function<void(Particle2D&, float)> m_updateFunc;
};

} /* namespace SnowEngine */
