/*
 * SpriteBatch.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#include "SpriteBatch.h"

#include <algorithm>

namespace SnowEngine
{

SpriteBatch::SpriteBatch() :
		m_vbo(0), m_vao(0), m_sortType(GlyphSortType::TEXTURE)
{

}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init(ShaderCache& shaderCache)
{
	m_shader = shaderCache.loadShaderFromData(VERT_SRC, FRAG_SRC, "__DeFaUlT__sPrItEbAtCh__ShAdEr__");
	if (!m_shader->hasAttributes())
	{
		m_shader->addAttribute("vertexPosition");
		m_shader->addAttribute("vertexUV");
		m_shader->addAttribute("vertexColor");
	}
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType)
{
	m_sortType = sortType;
	m_renderBatches.clear();
	m_glyphs.clear();
	m_glyphPointers.clear();
}

void SpriteBatch::end()
{
	sortGlyphys();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,
		float depth, float angle, const ColorRGBA8& color)
{
	m_glyphs.emplace_back(destRect, uvRect, texture, depth, angle, color);
	m_glyphPointers.push_back(&m_glyphs.back());
}

void SpriteBatch::renderBatch(const glm::mat4& projectionMatrix)
{
	m_shader->use();

	GLint pLoc = m_shader->getUniformLocation("P");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
	glBindVertexArray(m_vao);

	for (unsigned int i = 0; i < m_renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
	m_shader->unuse();
}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(m_glyphPointers.size() * 6);
	if (m_glyphPointers.empty())
	{
		return;
	}

	int cv = 0;
	m_renderBatches.emplace_back(0, 6, m_glyphPointers[0]->texture);
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomLeft;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->bottomRight;
	vertices[cv++] = m_glyphPointers[0]->topRight;
	vertices[cv++] = m_glyphPointers[0]->topLeft;
	for (unsigned int cg = 1; cg < m_glyphPointers.size(); cg++)
	{
		if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture)
		{
			m_renderBatches.emplace_back(cg * 6, 6, m_glyphPointers[cg]->texture);
		}
		else
		{
			m_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->bottomRight;
		vertices[cv++] = m_glyphPointers[cg]->topRight;
		vertices[cv++] = m_glyphPointers[cg]->topLeft;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	if (m_vao == 0)
	{
		glGenVertexArrays(1, &m_vao);
	}

	glBindVertexArray(m_vao);

	if (m_vbo == 0)
	{
		glGenBuffers(1, &m_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*) offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
			(void*) offsetof(Vertex, color));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphys()
{
	switch (m_sortType)
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
		break;
	case GlyphSortType::NONE:
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return a->depth < b->depth;
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return a->depth > b->depth;
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return a->texture < b->texture;
}

} /* namespace SnowEngine */
