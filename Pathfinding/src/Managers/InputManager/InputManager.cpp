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
#include "Game.h"
#include "GameState/GameState.h"

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

/**
 * \brief  Handle the key down event
 * \param event : the event to handle
 * \param _gridSprite : the grid sprite
 * \param _gameState : the game state
 */
void InputManager::HandleKeyDown(const sf::Event& event, const sf::Sprite& _gridSprite,GameState& _gameState)
{
	GameDataRef _data = _gameState.GetGameData();
	
	// Left click to place the start point
	if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && IsMouseOverSprite(_gridSprite, _data->m_window))
	{
		_gameState.PlacePiece(START_PIECE);
	}

	// Right click to place the end point
	if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Right == event.key.code && IsMouseOverSprite(_gridSprite, _data->m_window))
	{
		_gameState.PlacePiece(END_PIECE);
	}

	// Press W to place a wall
	if (sf::Event::KeyReleased == event.type && sf::Keyboard::W == event.key.code)
	{
		if (IsMouseOverSprite(_gridSprite, _data->m_window))
		{
			_gameState.PlacePiece(WALL_PIECE);
		}
	}

	// Press C to place a checkpoint
	if (sf::Event::KeyReleased == event.type && sf::Keyboard::C == event.key.code)
	{
		if (IsMouseOverSprite(_gridSprite, _data->m_window))
		{
			_gameState.PlacePiece(CHECKPOINT_PIECE);
		}
	}

	// Press P to place a portal
	if (sf::Event::KeyReleased == event.type && sf::Keyboard::P == event.key.code)
	{
		if (IsMouseOverSprite(_gridSprite, _data->m_window))
		{
			_gameState.PlacePiece(PORTAL_PIECE);
		}
	}
}
