#include "PauseState.h"
#include "defined.h"
#include "GameState/GameState.h"
#include "MainMenu/MainMenuState.h"

#include <sstream>
#include <iostream>

PauseState::PauseState(GameDataRef data) : _data(data)
{
}

void PauseState::Init()
{
	this->_data->m_assetManager.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
	this->_data->m_assetManager.LoadTexture("Resume Button", RESUME_BUTTON);
	this->_data->m_assetManager.LoadTexture("Home Button", HOME_BUTTON);

	this->_background.setTexture(this->_data->m_assetManager.GetTexture("Pause Background"));
	this->_resumeButton.setTexture(this->_data->m_assetManager.GetTexture("Resume Button"));
	this->_homeButton.setTexture(this->_data->m_assetManager.GetTexture("Home Button"));

	this->_resumeButton.setScale(0.1f, 0.1f);
	this->_homeButton.setScale(0.1f, 0.1f);

	this->_resumeButton.setPosition((SCREEN_WIDTH / 2) - (this->_resumeButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (this->_resumeButton.getGlobalBounds().height / 2));
	this->_homeButton.setPosition((SCREEN_WIDTH / 2) - (this->_homeButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3 * 2) - (this->_homeButton.getGlobalBounds().height / 2));
	
	this->_background.setScale(SCREEN_WIDTH / this->_background.getGlobalBounds().width, SCREEN_HEIGHT / this->_background.getGlobalBounds().height);	
}

void PauseState::HandleInput()
{
	sf::Event event;

	while (this->_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->m_window.close();
		}
		
		if (this->_data->m_inputManager.IsSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->m_window))
		{
			this->_data->machine.RemoveState();
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->m_window))
		{
			this->_data->machine.RemoveState();
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}
}

void PauseState::Update(float dt)
{
}

void PauseState::Draw(float dt)
{
	this->_data->m_window.clear();

	this->_data->m_window.draw(this->_background);
	this->_data->m_window.draw(this->_resumeButton);
	this->_data->m_window.draw(this->_homeButton);

	this->_data->m_window.display();
}
