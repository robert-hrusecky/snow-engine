/*
 * IGameScreen.h
 *
 *  Created on: Aug 5, 2015
 *      Author: Robert
 */

#pragma once

#include <SDL2/SDL.h>

#include "InputManager.h"
namespace SnowEngine
{

class IMainGame;

class IGameScreen
{
public:
	IGameScreen(IMainGame* game);
	virtual ~IGameScreen();

	virtual void onStart() = 0;
	virtual void onPause() = 0;
	virtual void update(float deltaTime, InputManager& inputManager) = 0;
	virtual void onEvent(const SDL_Event& evnt) = 0;
	virtual void draw() = 0;
protected:
	IMainGame* m_game;
};

} /* namespace SnowEngine */
