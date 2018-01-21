/*
 * timing.h
 *
 *  Created on: Jul 19, 2015
 *      Author: Robert
 */

#pragma once

namespace SnowEngine
{

class FPSLimiter
{
public:
	FPSLimiter();
	void init(float maxFPS);
	void setMaxFPS(float maxFPS);
	float getMaxFPS() const;
	void begin();
	void end();
	float calculateFPS();
private:
	float m_frameTimes[10];
	unsigned int m_startTicks, m_currentFrame, m_prevTicks;
	float m_maxFPS;
};


}  // namespace SnowEngine



