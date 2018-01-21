/*
 * ParticleBatch2D.cpp
 *
 *  Created on: Jul 31, 2015
 *      Author: Robert
 */

#include "ParticleBatch2D.h"

namespace SnowEngine
{

void defaultParticleUpdate(Particle2D& particle, float deltaTime)
{
	particle.position += deltaTime * particle.velocity;
}

ParticleBatch2D::ParticleBatch2D()
{
	// TODO Auto-generated constructor stub

}

ParticleBatch2D::~ParticleBatch2D()
{
	delete[] m_particles;
}

void ParticleBatch2D::init(int maxParticles, float decayRate, const GLTexture& texture, std::function<void(Particle2D&, float)> updateFunc)
{
	m_maxParticles = maxParticles;
	m_decayRate = decayRate;
	m_texture = texture;
	m_updateFunc = updateFunc;
	m_particles = new Particle2D[maxParticles];
}

void ParticleBatch2D::addParticle(const glm::vec2& position, const glm::vec2& velocity, const ColorRGBA8& color, float width)
{
	int i = findFreeParticle();
	m_particles[i].position = position;
	m_particles[i].velocity = velocity;
	m_particles[i].color = color;
	m_particles[i].width = width;
	m_particles[i].life = 1.0f;
}

void ParticleBatch2D::update(float deltaTime)
{
	for (int i = 0; i < m_maxParticles; i++)
	{
		if (m_particles[i].life > 0.0f)
		{
			m_updateFunc(m_particles[i], deltaTime);
			m_particles[i].life -= deltaTime * m_decayRate;
		}
	}
}

void ParticleBatch2D::draw(SpriteBatch* spriteBatch)
{
	static glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	for (int i = 0; i < m_maxParticles; i++)
	{
		if (m_particles[i].life > 0.0f)
		{
			glm::vec4 destRect(m_particles[i].position, m_particles[i].width, m_particles[i].width);
			spriteBatch->draw(destRect, uvRect, m_texture.id, 0.0f, 0.0f, m_particles[i].color);
		}
	}
}

int ParticleBatch2D::findFreeParticle()
{
	int prevFreeParticle = m_lastFreeParticle;

	for (; m_lastFreeParticle < m_maxParticles; m_lastFreeParticle++)
	{
		if (m_particles[m_lastFreeParticle].life <= 0.0f)
		{
			return m_lastFreeParticle;
		}
	}

	for (m_lastFreeParticle = 0; m_lastFreeParticle < prevFreeParticle; m_lastFreeParticle++)
	{
		if (m_particles[m_lastFreeParticle].life <= 0.0f)
		{
			return m_lastFreeParticle;
		}
	}

	return ++m_lastFreeParticle;
}

} /* namespace SnowEngine */
