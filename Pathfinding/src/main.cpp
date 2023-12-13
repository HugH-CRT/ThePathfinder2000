/**
* @file main.cpp
* @brief
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 12/10/2023
*/

#include "defined.h"
#include "logger.h"
#include "Game.h"

#include <iostream>

Game* gGame = nullptr;

/**
* @fn GetGame
* @brief  Get the game instance
* @return Game*
*/
Game* GetGame()
{
	return gGame;
}

/**
* @fn main
* @brief  Main function of the game
* @return exit code of the game
*/
int main() 
{
	Logger::setConsoleLog_ON();

	Logger::info("Start game ... ");
  
    gGame = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_WINDOW);
	gGame->Run();

	return EXIT_SUCCESS;
}