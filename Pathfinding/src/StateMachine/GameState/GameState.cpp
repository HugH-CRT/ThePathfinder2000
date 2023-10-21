#include "GameState.h"
#include "../defined.h"
#include "../PauseState/PauseState.h"

#include <sstream>
#include <iostream>

GameState::GameState(GameDataRef data) : _data( data )
{
}

void GameState::Init()
{
	this->_data->m_assetManager.LoadTexture("Pause Button", PAUSE_BUTTON);
	this->_data->m_assetManager.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	
	_background.setTexture(this->_data->m_assetManager.GetTexture("Game Background"));
	this->_background.setScale(SCREEN_WIDTH / this->_background.getLocalBounds().width, SCREEN_HEIGHT / this->_background.getLocalBounds().height);

	_pauseButton.setScale(0.3f, 0.3f);
	_pauseButton.setTexture(this->_data->m_assetManager.GetTexture("Pause Button"));

	_pauseButton.setPosition((SCREEN_WIDTH - _pauseButton.getGlobalBounds().width), _pauseButton.getPosition().y);
}

void GameState::HandleInput()
{
	sf::Event event;

	while (this->_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->m_window.close();
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->m_window))
		{
			this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
		}
	}
}

void GameState::Update(float dt)
{
}

void GameState::Draw(float dt)
{
	_data->m_window.clear();
	_data->m_window.draw(_background);
	_data->m_window.draw(_pauseButton);
	_data->m_window.display();
}
