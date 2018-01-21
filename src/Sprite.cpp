/*
 * Sprite.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: Robert
 */

#include "Sprite.h"

#include <cstddef>
#include "ResourceManager.h"
#include "VertexData.h"

namespace SnowEngine
{

Sprite::Sprite()
{
	m_vboID = 0;
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
	m_texture = nullptr;
}

Sprite::~Sprite()
{
	if (m_vboID != 0)
	{
		glDeleteBuffers(1, &m_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height, std::string filePath)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_texture = ResourceManager::getTexture(filePath);

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}

	Vertex vertexData[6];
	// First Triangle
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 0.0f);
	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 0.0f);
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 1.0f);
	// Second Triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 1.0f);
	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 1.0f);
	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture->id);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
