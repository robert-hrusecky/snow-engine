/*
 * VertexData.h
 *
 *  Created on: Jul 12, 2015
 *      Author: Robert
 */

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace SnowEngine
{

struct ColorRGBA8
{
	ColorRGBA8() :
		r(255), g(255), b(255), a(255)
	{
	}
	ColorRGBA8(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) :
		r(red), g(green), b(blue), a(alpha)
	{
	}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex
{
	glm::vec2 position;
	glm::vec2 uv;
	ColorRGBA8 color;

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	void setUV(float u, float v)
	{
		uv.x = u;
		uv.y = v;
	}
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.b = b;
		color.g = g;
		color.a = a;
	}

};

}
