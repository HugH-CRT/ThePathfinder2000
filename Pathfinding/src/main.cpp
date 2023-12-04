/**
* @file main.cpp
*
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
#include "macro.h"
#include "Game.h"

#include <iostream>

Game* gGame = nullptr;

/**
* @fn GetGame
* @brief  
* @return 
*/
Game* GetGame()
{
	return gGame;
}

/**
* @fn main
* @brief  
* @return 
*/
int main() 
{
	Logger::setConsoleLog_ON();

	Logger::info("Start game ... ");
  
    gGame = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_WINDOW);
	gGame->nb_columns = 15;
	gGame->nb_lines = 9;
	gGame->Run();

	DELETE_PTR(gGame)

	return EXIT_SUCCESS;
}