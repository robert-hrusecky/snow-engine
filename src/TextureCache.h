/*
 * TextureCache.h
 *
 *  Created on: Jul 14, 2015
 *      Author: Robert
 */

#pragma once

#include <map>
#include <string>
#include "GLTexture.h"

namespace SnowEngine
{

class TextureCache
{
public:
	TextureCache();
	~TextureCache();
	GLTexture* getTexture(std::string filePath);
private:
	std::map<std::string, GLTexture> m_textureMap;
};

}
