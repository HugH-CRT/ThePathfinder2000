#include "MainMenuState.h"
#include "defined.h"

#include <sstream>
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{
}

void MainMenuState::Init()
{
	this->_data->m_assetManager.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	this->_data->m_assetManager.LoadTexture("Game Title", MAIN_MENU_TITLE_PATH);
	this->_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	this->_data->m_assetManager.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);

	this->_background.setTexture(this->_data->m_assetManager.GetTexture("Main Menu Background"));
	this->title.setTexture(this->_data->m_assetManager.GetTexture("Game Title"));
	this->playButton.setTexture(this->_data->m_assetManager.GetTexture("Play Button"));
	//this->playButtonOuter.setTexture(this->_data->m_assetManager.GetTexture("Play Button Outer"));

	this->playButton.setPosition((SCREEN_WIDTH / 2) - (this->playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->playButton.getGlobalBounds().height / 2));
	//this->playButtonOuter.setPosition((SCREEN_WIDTH / 2) - (this->playButtonOuter.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->playButtonOuter.getGlobalBounds().height / 2));*/

	
	this->title.setScale(0.2, 0.2);
	this->title.setPosition((SCREEN_WIDTH / 2) - (this->title.getGlobalBounds().width / 2), this->title.getGlobalBounds().height * 0.1);	
	
	this->_background.setScale(SCREEN_WIDTH / this->_background.getLocalBounds().width, SCREEN_HEIGHT / this->_background.getLocalBounds().height);
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
		if (this->_data->m_inputManager.IsSpriteClicked(this->playButton, sf::Mouse::Left, this->_data->m_window))
		{
			std::cout << "Go to Game Screen" << std::endl;
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
	//this->_data->m_window.draw(this->playButtonOuter);
	this->_data->m_window.draw(this->title);

	this->_data->m_window.display();
}