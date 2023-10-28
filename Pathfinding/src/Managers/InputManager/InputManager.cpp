/**
* @file InputManager.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "InputManager.h"

/** 
* @fn IsSpriteClicked
* @brief Check if the sprite is clicked
* 
* @param object : the sprite to check
* @param button : the button to check
* @param window : the window to check
*/
bool InputManager::IsSpriteClicked(const sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		return IsMouseOverSprite(object, window);
	}

	return false;
}

/** 
* @fn GetMousePosition
* @brief Get the mouse position in the window
* @param window : the window to check
*/
sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

/** 
* @fn IsMouseOverSprite
* @brief Check if the mouse is over the sprite
* @param object : the sprite to check
* @param window : the window to check
*/
bool InputManager::IsMouseOverSprite(const sf::Sprite& object, const sf::RenderWindow& window)
{
	const sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width,
	                           object.getGlobalBounds().height);
	
	return tempRect.contains(sf::Mouse::getPosition(window));
}