/*
 * ResourceManager.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: Robert
 */

#include "ResourceManager.h"

namespace SnowEngine
{

TextureCache ResourceManager::m_textureCache;

GLTexture* ResourceManager::getTexture(std::string filePath)
{
	return m_textureCache.getTexture(filePath);
}

}
