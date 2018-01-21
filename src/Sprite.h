/*
 * Sprite.h
 *
 *  Created on: Jul 9, 2015
 *      Author: Robert
 */

#pragma once

#include <GL/glew.h>
#include <string>
#include "GLTexture.h"

namespace SnowEngine
{

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string filePath);
	void draw();
private:
	float m_x, m_y, m_width, m_height;
	GLuint m_vboID;
	GLTexture* m_texture;
};

}
