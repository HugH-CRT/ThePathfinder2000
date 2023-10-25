#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include<SFML/Graphics.hpp>

class InputManager
{
public: 
	InputManager() {}
	~InputManager() {}

	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	bool IsMouseOverSprite(sf::Sprite object, sf::RenderWindow& window);
};

#endif /* INPUT_MANAGER_H */