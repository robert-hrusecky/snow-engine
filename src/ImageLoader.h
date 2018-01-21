/*
 * ImageLoader.h
 *
 *  Created on: Jul 13, 2015
 *      Author: Robert
 */

#pragma once

#include <string>
#include <vector>
#include "GLTexture.h"

namespace SnowEngine
{

class ImageLoader
{
public:
	static void loadPNG(std::string filePath, GLTexture& texture);
	static void createTexture(GLuint* id, unsigned long width, unsigned long height, const void* pixels);
};

}
