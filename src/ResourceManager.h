/*
 * ResourceManager.h
 *
 *  Created on: Jul 14, 2015
 *      Author: Robert
 */

#pragma once

#include <string>
#include "TextureCache.h"

namespace SnowEngine
{

class ResourceManager
{
public:
	static GLTexture* getTexture(std::string filePath);

private:
	static TextureCache m_textureCache;
};

}
