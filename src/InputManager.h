/*
 * InputManager.h
 *
 *  Created on: Jul 19, 2015
 *      Author: Robert
 */

#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace SnowEngine
{

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();
	int getEvent(SDL_Event* evnt);
	void pressKey(unsigned int keyCode);
	void releaseKey(unsigned int keyCode);
	void setMouseCoords(int x, int y);
	bool isKeyDown(unsigned int keyCode);
	bool isKeyPressed(unsigned int keyCode);
	glm::vec2 getMouseCoords() const;
private:
	bool wasKeyDown(unsigned int keyCode);

	std::unordered_map<unsigned int, bool> m_keyMap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;
	glm::vec2 m_mouseCoords;
};

} /* namespace SnowEngine */
