/*
 * IMainGame.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: Robert
 */

#include "IMainGame.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <algorithm>

#include "IGameScreen.h"
#include "errors.h"

namespace SnowEngine
{

IMainGame::IMainGame(const char* windowName, int screenWidth, int screenHeight) :
		m_windowName(windowName), m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
}

IMainGame::~IMainGame()
{
	for (auto& it : m_screens)
	{
		delete it.second;
	}
}

void IMainGame::run()
{
	SnowEngine::init();
	m_window.create(m_windowName, m_screenWidth, m_screenHeight);
	m_fpsLimiter.init(60.0f);
	m_running = true;
	onStart();
	if (m_activeScreen == nullptr)
	{
		fatalError("No active screen");
	}
	while (m_running)
	{

		m_fpsLimiter.begin();
		m_inputManager.update();

		SDL_Event evnt;
		while (m_inputManager.getEvent(&evnt))
		{
			if (evnt.type == SDL_QUIT)
			{
				m_running = false;
			}
			m_activeScreen->onEvent(evnt);
		}

		m_activeScreen->update(m_desiredFrameTime, m_inputManager);

		if (!m_running)
		{
			break;
		}
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_activeScreen->draw();
		m_window.swap();
		m_fpsLimiter.end();
		m_fps = m_fpsLimiter.calculateFPS();
	}
	m_activeScreen->onPause();
	onStop();
	SnowEngine::quit();
}

void IMainGame::addScreen(IGameScreen* screen, const char* name)
{
	m_screens[name] = screen;
}

IGameScreen* IMainGame::getScreen(const char* name)
{
	return m_screens.find(name)->second;
}

void IMainGame::setActiveScreen(const char* name)
{
	IGameScreen* screen = getScreen(name);
	if (screen == nullptr)
	{
		fatalError("Tried to set unknown screen active");
	}
	if (m_activeScreen != nullptr)
	{
		m_activeScreen->onPause();
	}
	screen->onStart();
	m_activeScreen = screen;
}

IGameScreen* IMainGame::getActiveScreen() const
{
	return m_activeScreen;
}

float IMainGame::getDesiredFPS() const
{
	return 1000.0f / m_desiredFrameTime;
}

void IMainGame::setDesiredFPS(float fps)
{
	m_desiredFrameTime = 1000.0f / fps;
}

int IMainGame::getScreenWidth() const
{
	return m_screenWidth;
}

int IMainGame::getScreenHeight() const
{
	return m_screenHeight;
}

ShaderCache& IMainGame::getShaderCache()
{
	return m_shaderCache;
}

} /* namespace SnowEngine */
