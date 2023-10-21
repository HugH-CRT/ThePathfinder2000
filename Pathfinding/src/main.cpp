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
#include "macro.h"
#include "defined.h"
#include "Game.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

/**
* @fn main
*/
int main() 
{
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_WINDOW);
	return EXIT_SUCCESS;
}