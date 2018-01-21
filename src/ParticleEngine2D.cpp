/*
 * ParticleEngine2D.cpp
 *
 *  Created on: Jul 31, 2015
 *      Author: Robert
 */

#include "ParticleEngine2D.h"

#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

namespace SnowEngine
{

ParticleEngine2D::ParticleEngine2D()
{
	// TODO Auto-generated constructor stub

}

ParticleEngine2D::~ParticleEngine2D()
{
	for (auto& batch : m_batches)
	{
		delete batch;
	}
}

void ParticleEngine2D::addParticleBatch(ParticleBatch2D* particleBatch)
{
	m_batches.push_back(particleBatch);
}

void ParticleEngine2D::update(float deltaTime)
{
	for (auto& batch : m_batches)
	{
		batch->update(deltaTime);
	}
}

void ParticleEngine2D::draw(SpriteBatch* spriteBatch, const glm::mat4& projectionMatrix)
{
	spriteBatch->begin();
	for (auto& batch : m_batches)
	{
		batch->draw(spriteBatch);
	}
	spriteBatch->end();
	spriteBatch->renderBatch(projectionMatrix);
}

} /* namespace SnowEngine */
