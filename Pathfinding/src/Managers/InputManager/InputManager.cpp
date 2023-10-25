#include "InputManager.h"

bool InputManager::IsSpriteClicked(const sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		return IsMouseOverSprite(object, window);
	}

	return false;
}

sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

bool InputManager::IsMouseOverSprite(const sf::Sprite& object, const sf::RenderWindow& window)
{
	const sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (tempRect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}

	return false;
}