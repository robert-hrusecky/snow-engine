/*
 * InputManager.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: Robert
 */

#include "InputManager.h"

namespace SnowEngine
{

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	m_previousKeyMap = m_keyMap;
}

int InputManager::getEvent(SDL_Event* evnt)
{
	int rVal = SDL_PollEvent(evnt);
	if (rVal)
	{
		switch (evnt->type)
		{
		case SDL_MOUSEMOTION:
			setMouseCoords(evnt->motion.x, evnt->motion.y);
			break;
		case SDL_KEYDOWN:
			pressKey(evnt->key.keysym.sym);
			break;
		case SDL_KEYUP:
			releaseKey(evnt->key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			pressKey(evnt->button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			releaseKey(evnt->button.button);
			break;
		}
	}
	return rVal;
}

void InputManager::pressKey(unsigned int keyCode)
{
	m_keyMap[keyCode] = true;
}

void InputManager::releaseKey(unsigned int keyCode)
{
	m_keyMap[keyCode] = false;
}


void InputManager::setMouseCoords(int x, int y)
{
	m_mouseCoords.x = x;
	m_mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyCode)
{
	auto it = m_keyMap.find(keyCode);
	if (it != m_keyMap.end())
	{
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(unsigned int keyCode)
{
	return isKeyDown(keyCode) && !wasKeyDown(keyCode);
}

glm::vec2 InputManager::getMouseCoords() const
{
	return m_mouseCoords;
}

bool InputManager::wasKeyDown(unsigned int keyCode)
{
	auto it = m_previousKeyMap.find(keyCode);
	if (it != m_previousKeyMap.end())
	{
		return it->second;
	}
	return false;
}

} /* namespace SnowEngine */
