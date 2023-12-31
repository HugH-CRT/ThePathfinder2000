/**
* @file InputManager.h
*
* @brief Manage the inputs of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include<SFML/Graphics.hpp>

class GameState;

/**
* @class InputManager
* @brief Manage the inputs of the game
*/
class InputManager
{
public: 
	InputManager() = default;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() = default;

	bool IsSpriteClicked(const sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow& window);
	bool IsMouseOverSprite(const sf::Sprite& object, const sf::RenderWindow& window);

	void HandleKeyDown(const sf::Event& event, const sf::Sprite& _gridSprite,GameState& _gameState);
	
	sf::Vector2i GetMousePosition(const sf::RenderWindow& window);
};

#endif /* INPUT_MANAGER_H */