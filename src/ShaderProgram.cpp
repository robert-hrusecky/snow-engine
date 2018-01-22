/*
 * GLSLProgram.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: Robert
 */

#include "ShaderProgram.h"

#include <cstdio>
#include "errors.h"
#include "IOManager.h"

namespace SnowEngine
{

ShaderProgram::ShaderProgram() :
		m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

bool ShaderProgram::hasAttributes()
{
	return m_numAttributes > 0;
}

void ShaderProgram::use()
{
	glUseProgram(m_programID);
	/*for (int i = 0; i < m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}*/
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint ShaderProgram::getUniformLocation(const std::string& uniformName)
{
	auto it = m_uniforms.find(uniformName);
	if (it != m_uniforms.end())
	{
		return it->second;
	}

	GLuint location =  glGetUniformLocation(m_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " not found in shader.");
	}

	m_uniforms[uniformName] = location;

	return location;
}

ShaderCache::~ShaderCache()
{
	for (auto& it : m_shaders)
	{
		if (it.second.m_programID)
		{
			glDeleteProgram(it.second.m_programID);
		}
	}
}

ShaderProgram* ShaderCache::loadShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string name = vertexPath;
	name.resize(name.find("."));

	auto it = m_shaders.find(name);

	if (it != m_shaders.end())
	{
		return &it->second;
	}

	std::string vertexData;
	std::string fragmentData;
	IOManager::readFileToBuffer(vertexPath, vertexData);
	IOManager::readFileToBuffer(fragmentPath, fragmentData);
	return loadShaderFromData(vertexData.c_str(), fragmentData.c_str(), name);
}

ShaderProgram* ShaderCache::loadShaderFromData(const char* vertexData, const char* fragmentData, const std::string& name)
{
	auto it = m_shaders.find(name);

	if (it != m_shaders.end())
	{
		return &it->second;
	}

	ShaderProgram shader;
	shader.m_programID = glCreateProgram();
	shader.m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (shader.m_vertexShaderID == 0)
	{
		fatalError("Vertex shader failed to be created!");
	}

	shader.m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (shader.m_fragmentShaderID == 0)
	{
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(vertexData, shader.m_vertexShaderID);
	compileShader(fragmentData, shader.m_fragmentShaderID);

	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a _programID.

	//Attach our shaders to our _programID
	glAttachShader(shader.m_programID, shader.m_vertexShaderID);
	glAttachShader(shader.m_programID, shader.m_fragmentShaderID);

	//Link our _program
	glLinkProgram(shader.m_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(shader.m_programID, GL_LINK_STATUS, (int *) &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shader.m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		GLchar* infoLog = new GLchar[maxLength];
		glGetProgramInfoLog(shader.m_programID, maxLength, &maxLength, infoLog);

		//We don't need the _programID anymore.
		glDeleteProgram(shader.m_programID);
		//Don't leak shaders either.
		glDeleteShader(shader.m_vertexShaderID);
		glDeleteShader(shader.m_fragmentShaderID);

		std::printf("%s\n", infoLog);
		delete[] infoLog;
		fatalError("Shaders failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(shader.m_programID, shader.m_vertexShaderID);
	glDetachShader(shader.m_programID, shader.m_fragmentShaderID);
	glDeleteShader(shader.m_vertexShaderID);
	glDeleteShader(shader.m_fragmentShaderID);

	m_shaders[name] = shader;

	return &m_shaders[name];
}

void ShaderCache::deleteShader(const std::string& name)
{
	auto it = m_shaders.find(name);

	if (it == m_shaders.end())
	{
		return;
	}

	if (it->second.m_programID)
	{
		glDeleteProgram(it->second.m_programID);
		it->second.m_programID = 0;
	}
}

void ShaderCache::compileShader(const char* contents, GLuint id)
{
	glShaderSource(id, 1, &contents, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(id, maxLength, &maxLength,
				errorLog);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		std::printf("%s\n", errorLog);
		delete[] errorLog;
		fatalError("Shader failed to compile.");
	}
}

}
