/*
 * TextureCache.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: Robert
 */

#include "TextureCache.h"

#include "ImageLoader.h"

namespace SnowEngine
{

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture* TextureCache::getTexture(std::string filePath)
{
	auto mit = m_textureMap.find(filePath);

	if (mit == m_textureMap.end())
	{
		GLTexture newTexture;
		ImageLoader::loadPNG(filePath, newTexture);
		m_textureMap.insert(make_pair(filePath, newTexture));
		mit = m_textureMap.find(filePath);
	}

	return &(mit->second);
}

}
