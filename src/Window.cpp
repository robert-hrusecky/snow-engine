/*
 * Window.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#include "Window.h"

#include <GL/glew.h>

#include "gferrors.h"

namespace SnowEngine
{

Window::Window() :
		m_sdlWindow(nullptr), m_screenWidth(0), m_screenHeight(0)
{
}

Window::~Window()
{
}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int flags)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	Uint32 flgs = SDL_WINDOW_OPENGL;

	if (flags & INVISIBLE)
	{
		flgs |= SDL_WINDOW_HIDDEN;
	}
	else if (flags & FULLSCREEN)
	{
		flgs |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else if (flags & BORDERLESS)
	{
		flgs |= SDL_WINDOW_BORDERLESS;
	}
	m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, flgs);
	if (m_sdlWindow == nullptr)
	{
		fatalError(SDL_GetError());
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
	if (glContext == nullptr)
	{
		fatalError("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize GLEW");
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	SDL_GL_SetSwapInterval((~flags & VSYNC_OFF) >> 3);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

int Window::getScreenWidth()
{
	return m_screenWidth;
}

int Window::getScreenHeight()
{
	return m_screenHeight;
}

void Window::swap()
{
	SDL_GL_SwapWindow(m_sdlWindow);
}

}
