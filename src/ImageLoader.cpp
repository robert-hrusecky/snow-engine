/*
 * ImageLoader.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: Robert
 */

#include "ImageLoader.h"

#include <vector>
#include <GL/glew.h>

#include "errors.h"
#include "IOManager.h"
#include "picopng.h"

namespace SnowEngine
{

void ImageLoader::loadPNG(std::string filePath, GLTexture& texture)
{
	std::vector<unsigned char> in;
	if (!IOManager::readFileToBuffer(filePath, in))
	{
		fatalError("Failed to load PNG file to buffer");
	}

	std::vector<unsigned char> out;
	unsigned long width, height;
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode)
	{
		fatalError("picopng failed with error: " + std::to_string(errorCode));
	}

	createTexture(&texture.id, width, height, &out[0]);

	texture.width = width;
	texture.height = height;
}

void ImageLoader::createTexture(GLuint* id, unsigned long width, unsigned long height, const void* pixels)
{
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
