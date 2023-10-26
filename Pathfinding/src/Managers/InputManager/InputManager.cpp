#include "InputManager.h"

/*
 * Brief : Check if the sprite is clicked
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

/*
 * Brief : Get the mouse position in the window
 *
 * @param window : the window to check
 */
sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

/*
 * Brief : Check if the mouse is over the sprite
 *
 * @param object : the sprite to check
 * @param window : the window to check
 */
bool InputManager::IsMouseOverSprite(const sf::Sprite& object, const sf::RenderWindow& window)
{
	const sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width,
	                           object.getGlobalBounds().height);
	
	return tempRect.contains(sf::Mouse::getPosition(window));
}