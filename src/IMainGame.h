/*
 * IMainGame.h
 *
 *  Created on: Aug 5, 2015
 *      Author: Robert
 */

#pragma once

#include <map>
#include <string>

#include "SnowEngine.h"
#include "timing.h"
#include "Window.h"
#include "InputManager.h"
#include "ShaderProgram.h"

namespace SnowEngine
{

class IGameScreen;

class IMainGame
{
public:
	IMainGame(const char* windowName, int screenWidth, int screenHeight);
	virtual ~IMainGame();

	virtual void onStart() = 0;
	virtual void onStop() = 0;

	void run();
	void addScreen(IGameScreen* screen, const char* name);
	IGameScreen* getScreen(const char* name);
	void setActiveScreen(const char* name);
	IGameScreen* getActiveScreen() const;

	float getDesiredFPS() const;
	void setDesiredFPS(float fps);

	int getScreenWidth() const;
	int getScreenHeight() const;

	ShaderCache& getShaderCache();

protected:
	SnowEngine::Window m_window;
	SnowEngine::InputManager m_inputManager;
	SnowEngine::FPSLimiter m_fpsLimiter;
	SnowEngine::ShaderCache m_shaderCache;
	bool m_running = false;
	float m_fps = 60.0f;
	const char* m_windowName;
	int m_screenWidth, m_screenHeight;
	float m_desiredFrameTime = 16.6666666667f; ///< Frame time for 60fps
private:
	std::map<std::string, IGameScreen*> m_screens;
	IGameScreen* m_activeScreen = nullptr;
};

} /* namespace SnowEngine */
