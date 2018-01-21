/*
 * ParticleEngine2D.h
 *
 *  Created on: Jul 31, 2015
 *      Author: Robert
 */

#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace SnowEngine
{

class ParticleBatch2D;
class SpriteBatch;

class ParticleEngine2D
{
public:
	ParticleEngine2D();
	~ParticleEngine2D();
	void addParticleBatch(ParticleBatch2D* particleBatch);
	void update(float deltaTime);
	void draw(SpriteBatch* spriteBatch, const glm::mat4& projectionMatrix);
private:
	std::vector<ParticleBatch2D*> m_batches;
};

} /* namespace SnowEngine */
