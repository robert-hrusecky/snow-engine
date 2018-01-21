/*
 * SnowEngine.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: Robert
 */

#include "SnowEngine.h"

#include <SDL2/SDL.h>

namespace SnowEngine
{

int init()
{
	//Initailize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return 0;
}

}
