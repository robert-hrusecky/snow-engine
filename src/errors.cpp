/*
 * errors.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: Robert
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include "errors.h"

namespace SnowEngine
{

void fatalError(std::string message)
{
	std::cout << message << std::endl;
	std::cout << "Press any key to continue...";
	int a;
	std::cin >> a;
	SDL_Quit();
	exit(1);
}

}
