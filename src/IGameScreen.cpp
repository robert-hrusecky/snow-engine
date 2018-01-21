/*
 * IGameScreen.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: Robert
 */

#include "IGameScreen.h"
#include "IMainGame.h"

namespace SnowEngine
{

IGameScreen::IGameScreen(IMainGame* game) :
		m_game(game)
{
}

IGameScreen::~IGameScreen()
{
}

} /* namespace SnowEngine */
