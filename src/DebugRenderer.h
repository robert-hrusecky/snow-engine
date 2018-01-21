/*
 * DebugRenderer.h
 *
 *  Created on: Aug 20, 2015
 *      Author: Robert
 */

#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "ShaderProgram.h"
#include "VertexData.h"

namespace SnowEngine
{

class DebugRenderer
{
public:
	static constexpr const char* VERT_SRC =
			R"(#version 130
in vec2 vertexPosition;
in vec4 vertexColor;
out vec4 fragmentColor;
uniform mat4 P;
void main()
{
	gl_Position = P * vec4(vertexPosition, 0.0, 1.0);
	
	fragmentColor = vertexColor;
})";

	static constexpr const char* FRAG_SRC =
			R"(#version 130
in vec4 fragmentColor;
out vec4 color;
void main()
{
	color = fragmentColor;
})";

	DebugRenderer();
	~DebugRenderer();

	void init(ShaderCache& shaderCache);
	void end();
	void drawBox(const glm::vec4& rect, float angle, const ColorRGBA8& color);
	void drawCircle(const glm::vec2& position, float radius, const ColorRGBA8& color,
			unsigned int numVerts = 100);
	void drawPolygon(const glm::vec2& position, const std::vector<glm::vec2>& verts, float angle,
			const ColorRGBA8& color);
	void render(const glm::mat4& projectionMatrix, float lineWidth = 1.0f);

	struct DebugVertex
	{
		glm::vec2 position;
		ColorRGBA8 color;
	};
private:
	std::vector<DebugVertex> m_verts;
	std::vector<GLuint> m_indices;
	ShaderProgram* m_shader = nullptr;
	GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;
	unsigned int m_numElements = 0;
};

} /* namespace SnowEngine */
