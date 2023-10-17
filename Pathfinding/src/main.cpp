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

#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}