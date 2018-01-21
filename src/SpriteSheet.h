/*
 * SpriteSheet.h
 *
 *  Created on: Jan 23, 2017
 *      Author: Robert
 */

#pragma once
#include <string>
#include <vector>

#include "GLTexture.h"
#include "SpriteAnimation.h"
namespace SnowEngine
{

class SpriteSheet
{
public:
	SpriteSheet();
	void init(const std::string& filePath, const GLTexture& textrue);
	SpriteAnimation getAnimation(int index);
private:
	std::vector<SpriteAnimation> m_anims;

};

} /* namespace SnowEngine */
