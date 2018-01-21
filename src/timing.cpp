/*
 * timing.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: Robert
 */

#include "timing.h"

#include <SDL2/SDL.h>
#include <iostream>

namespace SnowEngine
{

FPSLimiter::FPSLimiter() :
		m_startTicks(0), m_currentFrame(0), m_prevTicks(0), m_maxFPS(60.0f)
{
}

void FPSLimiter::init(float maxFPS)
{
	setMaxFPS(maxFPS);
	m_prevTicks = SDL_GetTicks();
}

void FPSLimiter::setMaxFPS(float maxFPS)
{
	m_maxFPS = maxFPS;
}

float FPSLimiter::getMaxFPS() const
{
	return m_maxFPS;
}

void FPSLimiter::begin()
{
	m_startTicks = SDL_GetTicks();
}

void FPSLimiter::end()
{
	int frameTicks = SDL_GetTicks() - m_startTicks;
	if (1000.0f / m_maxFPS > frameTicks)
	{
		SDL_Delay((Uint32) (1000.0f / m_maxFPS - frameTicks));
	}
}

float FPSLimiter::calculateFPS()
{
	int currentTicks = SDL_GetTicks();

	int frameTime = currentTicks - m_prevTicks;
	m_frameTimes[m_currentFrame % 10] = frameTime;
	m_prevTicks = currentTicks;

	int count = m_currentFrame < 10 ? m_currentFrame : 10;

	float frameTimeSum = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeSum += m_frameTimes[i];
	}

	m_currentFrame++;
	return frameTimeSum == 0 ? m_maxFPS : 1000.0f * count / frameTimeSum;
}

}  // namespace SnowEngine


