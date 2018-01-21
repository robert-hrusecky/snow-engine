/*
 * Window.h
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace SnowEngine
{

enum WindowFlags
{
	INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, VSYNC_OFF = 0x8
};

class Window
{
public:
	Window();
	~Window();

	int create(std::string windowName, int screenWidth, int screenHeight, unsigned int flags = 0);
	int getScreenWidth();
	int getScreenHeight();
	void swap();

private:
	SDL_Window* m_sdlWindow;
	int m_screenWidth, m_screenHeight;
};

}
