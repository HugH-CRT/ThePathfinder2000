/**
* @file main.cpp
* @brief
*
* @author hugo.carricart@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 12/10/2023
*/
#include <iostream>

#include "defined.h"
#include "logger.h"
#include "Game.h"

Game* gGame = nullptr;

Game* GetGame()
{
	return gGame;
}

/**
* @fn main
*/
int main() 
{
	Logger::setConsoleLog_ON();

	Logger::info("Start game ... ");
  
    gGame = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_WINDOW);
	gGame->Run();

	return EXIT_SUCCESS;
}