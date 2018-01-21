/*
 * SpriteBatch.h
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "ShaderProgram.h"
#include "VertexData.h"

namespace SnowEngine
{

enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph
{
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint tex, float dpth, float angle, const ColorRGBA8& color) :
		texture(tex), depth(dpth)
	{
		glm::vec2 pos(destRect.x, destRect.y);
		glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);
		float cosA = glm::cos(angle);
		float sinA = glm::sin(angle);
		glm::mat2 rot(cosA, sinA, -sinA, cosA);

		topLeft.color = color;
		topLeft.position = rot * glm::vec2(-halfDims.x, halfDims.y) + pos;
		topLeft.setUV(uvRect.x, uvRect.y);

		bottomLeft.color = color;
		bottomLeft.position = rot * glm::vec2(-halfDims.x, -halfDims.y) + pos;
		bottomLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		topRight.color = color;
		topRight.position = rot * glm::vec2(halfDims.x, halfDims.y) + pos;
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		bottomRight.color = color;
		bottomRight.position = rot * glm::vec2(halfDims.x, -halfDims.y) + pos;
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

struct RenderBatch
{
	RenderBatch(GLuint off, GLuint verts, GLuint tex) :
		offset(off), numVertices(verts), texture(tex)
	{
	}

	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	static constexpr const char* VERT_SRC =
				R"(#version 130
in vec2 vertexPosition;
in vec2 vertexUV;
in vec4 vertexColor;
out vec2 fragmentUV;
out vec4 fragmentColor;
uniform mat4 P;

void main()
{
	gl_Position = P * vec4(vertexPosition, 0.0, 1.0);
	
	fragmentUV = vertexUV;
	fragmentColor = vertexColor;
})";

	static constexpr const char* FRAG_SRC =
			R"(#version 130

in vec2 fragmentUV;
in vec4 fragmentColor;
out vec4 color;
uniform sampler2D tex;

void main()
{
	color = vec4(fragmentColor.rg, fragmentColor.ba) * texture(tex, fragmentUV);
})";

	SpriteBatch();
	~SpriteBatch();

	void init(ShaderCache& shaderCache);

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, float angle = 0.0f, const ColorRGBA8& color = ColorRGBA8(255, 255, 255, 255));
	void renderBatch(const glm::mat4& projectionMatrix);
private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphys();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	ShaderProgram* m_shader;

	GLuint m_vbo, m_vao;

	GlyphSortType m_sortType;

	std::vector<Glyph> m_glyphs;
	std::vector<Glyph*> m_glyphPointers;
	std::vector<RenderBatch> m_renderBatches;
};

} /* namespace SnowEngine */
