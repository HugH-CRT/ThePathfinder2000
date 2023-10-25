#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		return IsMouseOverSprite(object, window);
	}

	return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

bool InputManager::IsMouseOverSprite(sf::Sprite object, sf::RenderWindow& window)
{
	sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (tempRect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}

	return false;
}
