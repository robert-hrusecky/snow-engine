/*
 * DebugRenderer.cpp
 *
 *  Created on: Aug 20, 2015
 *      Author: Robert
 */

#include "DebugRenderer.h"
#include <string>

#include "constants.h"
namespace SnowEngine
{

DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
	}
	if (m_vbo)
	{
		glDeleteBuffers(1, &m_vbo);
	}
	if (m_ibo)
	{
		glDeleteBuffers(1, &m_ibo);
	}
}

void DebugRenderer::init(ShaderCache& shaderCache)
{
	m_shader = shaderCache.loadShaderFromData(VERT_SRC, FRAG_SRC, "__DeFaUlT__dEbUg__ShAdEr__");
	if (!m_shader->hasAttributes())
	{
		m_shader->addAttribute("vertexPosition");
		m_shader->addAttribute("vertexColor");
	}

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*) offsetof(DebugVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*) offsetof(DebugVertex, color));

	glBindVertexArray(0);
}

void DebugRenderer::end()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_verts.size() * sizeof(DebugVertex), m_verts.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_numElements = m_indices.size();
	m_indices.clear();
	m_verts.clear();

}

void DebugRenderer::drawBox(const glm::vec4& rect, float angle, const ColorRGBA8& color)
{
	glm::vec2 halfDims(rect.z / 2.0f, rect.w / 2.0f);
	glm::vec2 pos(rect.x, rect.y);

	float cosA = glm::cos(angle);
	float sinA = glm::sin(angle);

	glm::mat2 rot(cosA, sinA, -sinA, cosA);

	unsigned int i = m_verts.size();
	m_verts.resize(m_verts.size() + 4);

	m_verts[i].position = rot * glm::vec2(-halfDims.x, halfDims.y) + pos;
	m_verts[i + 1].position = rot * glm::vec2(-halfDims.x, -halfDims.y) + pos;
	m_verts[i + 2].position = rot * glm::vec2(halfDims.x, -halfDims.y) + pos;
	m_verts[i + 3].position = rot * glm::vec2(halfDims.x, halfDims.y) + pos;

	for (unsigned int j = i; j < i + 4; j++)
	{
		m_verts[j].color = color;
	}

	m_indices.reserve(m_indices.size() + 8);
	for (unsigned int j = i; j < i + 3;)
	{
		m_indices.push_back(j);
		m_indices.push_back(++j);
	}

	m_indices.push_back(i + 3);
	m_indices.push_back(i);

}

void DebugRenderer::drawCircle(const glm::vec2& position, float radius, const ColorRGBA8& color, unsigned int numVerts)
{
	float angle = 2.0f * PI / numVerts;
	float cosA = glm::cos(angle);
	float sinA = glm::sin(angle);
	glm::mat2 rot(cosA, sinA, -sinA, cosA);

	unsigned int i = m_verts.size();
	m_verts.resize(m_verts.size() + numVerts);
	glm::vec2 terminal(radius, 0.0f);
	for (unsigned int j = 0; j < numVerts; j++)
	{
		m_verts[i + j].position = terminal;
		m_verts[i + j].color = color;
		terminal = rot * terminal;
	}
	m_indices.reserve(m_indices.size() + numVerts * 2);
	for (unsigned int j = i; j < i + numVerts - 1;)
	{
		m_indices.push_back(j);
		m_indices.push_back(++j);
	}
	m_indices.push_back(i + numVerts - 1);
	m_indices.push_back(i);
}

void DebugRenderer::drawPolygon(const glm::vec2& position, const std::vector<glm::vec2>& verts, float angle, const ColorRGBA8& color)
{
	unsigned int i = m_verts.size();
	m_verts.resize(m_verts.size() + verts.size());

	float cosA = glm::cos(angle);
	float sinA = glm::sin(angle);
	glm::mat2 rot(cosA, sinA, -sinA, cosA);

	for (unsigned int j = 0; j < verts.size(); j++)
	{
		m_verts[i + j].position = rot * verts[j] + position;
		m_verts[i + j].color = color;
	}
	m_indices.reserve(m_indices.size() + verts.size() * 2);
	for (unsigned int j = i; j < i + verts.size() - 1;)
	{
		m_indices.push_back(j);
		m_indices.push_back(++j);
	}
	m_indices.push_back(i + verts.size() - 1);
	m_indices.push_back(i);
}

void DebugRenderer::render(const glm::mat4& projectionMatrix, float lineWidth)
{
	m_shader->use();

	GLint pLoc = m_shader->getUniformLocation("P");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	glLineWidth(lineWidth);
	glBindVertexArray(m_vao);
	glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	m_shader->unuse();
}

} /* namespace SnowEngine */
