#include "MainMenuState.h"
#include "defined.h"
#include "GameState/GameState.h"

#include <sstream>
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{
}

void MainMenuState::Init()
{
	LoadTextures();
	SetTextures();

	this->title.setScale(0.2, 0.2);
	this->_background.setScale(SCREEN_WIDTH / this->_background.getLocalBounds().width, SCREEN_HEIGHT / this->_background.getLocalBounds().height);

	this->playButton.setPosition((SCREEN_WIDTH / 2) - (this->playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->playButton.getGlobalBounds().height / 2));
	this->title.setPosition((SCREEN_WIDTH / 2) - (this->title.getGlobalBounds().width / 2), this->title.getGlobalBounds().height * 0.1);	
}

void MainMenuState::HandleInput()
{
	sf::Event event;
	
	while ( this->_data->m_window.pollEvent( event ) )
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->m_window.close();
		}
		
		// Start button
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->_data->m_inputManager.IsMouseOverSprite(this->playButton, this->_data->m_window))
		{
			this->_data->machine.AddState(StateRef(new GameState(_data)), true); 
		}
	}
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Draw(float dt)
{
	this->_data->m_window.clear();

	this->_data->m_window.draw(this->_background);
	this->_data->m_window.draw(this->playButton);
	this->_data->m_window.draw(this->title);

	this->_data->m_window.display();
}

void MainMenuState::LoadTextures()
{
	this->_data->m_assetManager.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	this->_data->m_assetManager.LoadTexture("Game Title", MAIN_MENU_TITLE_PATH);
	this->_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	this->_data->m_assetManager.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
}

void MainMenuState::SetTextures()
{
	this->_background.setTexture(this->_data->m_assetManager.GetTexture("Main Menu Background"));
	this->title.setTexture(this->_data->m_assetManager.GetTexture("Game Title"));
	this->playButton.setTexture(this->_data->m_assetManager.GetTexture("Play Button"));
}