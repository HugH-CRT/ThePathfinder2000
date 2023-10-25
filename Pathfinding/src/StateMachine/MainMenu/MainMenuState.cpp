#include "MainMenuState.h"
#include "defined.h"
#include "GameState/GameState.h"

#include <sstream>
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) 
	: _data(data)
{
}

void MainMenuState::Init()
{
	LoadTextures();
	SetTextures();

	title.setScale(0.2f, 0.2f);
	_background.setScale(SCREEN_WIDTH / _background.getLocalBounds().width, SCREEN_HEIGHT / _background.getLocalBounds().height);

	playButton.setPosition((SCREEN_WIDTH / 2) - (playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (playButton.getGlobalBounds().height / 2));
	title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height * 0.1f);	
}

void MainMenuState::HandleInput()
{
	sf::Event event{};
	
	while ( _data->m_window.pollEvent( event ) )
	{
		if (sf::Event::Closed == event.type)
		{
			_data->m_window.close();
		}
		
		// Start button
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(playButton, _data->m_window))
		{
			_data->machine.AddState(StateRef(new GameState(_data)), true); 
		}
	}
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Draw(float dt)
{
	_data->m_window.clear();

	_data->m_window.draw(_background);
	_data->m_window.draw(playButton);
	_data->m_window.draw(title);

	_data->m_window.display();
}

void MainMenuState::LoadTextures()
{
	_data->m_assetManager.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	_data->m_assetManager.LoadTexture("Game Title", MAIN_MENU_TITLE_PATH);
	_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	_data->m_assetManager.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
}

void MainMenuState::SetTextures()
{
	_background.setTexture(_data->m_assetManager.GetTexture("Main Menu Background"));
	title.setTexture(_data->m_assetManager.GetTexture("Game Title"));
	playButton.setTexture(_data->m_assetManager.GetTexture("Play Button"));
}