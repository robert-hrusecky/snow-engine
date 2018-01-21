/*
 * GLSLProgram.h
 *
 *  Created on: Jul 12, 2015
 *      Author: Robert
 */

#pragma once

#include <string>
#include <map>
#include <GL/glew.h>

namespace SnowEngine
{

class ShaderProgram
{
public:
	friend class ShaderCache;
	ShaderProgram();
	~ShaderProgram();

	void addAttribute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& uniformName);

	bool hasAttributes();

	void use();
	void unuse();
private:
	int m_numAttributes;
	GLuint m_programID;
	GLuint m_vertexShaderID, m_fragmentShaderID;
	std::map<std::string, GLint> m_uniforms;
};

class ShaderCache
{
public:
	~ShaderCache();
	ShaderProgram* loadShader(const std::string& vertexPath, const std::string& fragmentPath);
	ShaderProgram* loadShaderFromData(const char* vertexData, const char* fragmentData, const std::string& name);
	void deleteShader(const std::string& name);
private:
	void compileShader(const char* contents, GLuint id);
	std::map<std::string, ShaderProgram> m_shaders;
};

}
