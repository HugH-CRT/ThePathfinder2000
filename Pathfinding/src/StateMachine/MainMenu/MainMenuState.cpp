/**
* @file MainMenuState.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "MainMenuState.h"
#include "defined.h"
#include "GameState/GameState.h"
#include "UI/UIWidget.h"
#include "UI/MainMenuWidget.h"

#include <sstream>

/**
* @fn MainMenuState
* @brief  
* @param data
*/
MainMenuState::MainMenuState(GameDataRef data) 
	: _data(std::move(data))
{
}

MainMenuState::~MainMenuState()
{
	if (_MainMenuUi != nullptr) {
		delete _MainMenuUi;
		_MainMenuUi = nullptr;
	}
}

/**
* @fn Init
* @brief  Initialize the state
*         - Load & set the textures & set scale & position	
*/
void MainMenuState::Init()
{
	LoadTextures();
	SetTextures();
	SetScales();
	SetPositions();
	_MainMenuUi = new MainMenuWidget(SCREEN_WIDTH, SCREEN_HEIGHT, _data);
}

/**
* @fn HandleInput
* @brief Handle the user inputs  
*/
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
			_data->machine.AddState(std::make_unique<GameState>(_data), true); 
		}
	}
}

/**
* @fn Update
* @brief  
* @param dt
*/
void MainMenuState::Update(float dt)
{
}

/**
* @fn SetScales
* @brief Set the scale of the elements  
*/
void MainMenuState::SetScales()
{
	title.setScale(0.2f, 0.2f);
	_background.setScale(SCREEN_WIDTH / _background.getLocalBounds().width,
						 SCREEN_HEIGHT / _background.getLocalBounds().height);
}

/**
* @fn SetPositions
* @brief  
*/
void MainMenuState::SetPositions()
{
	playButton.setPosition(SCREEN_WIDTH / 2 - playButton.getGlobalBounds().width / 2,
						   SCREEN_HEIGHT / 2 - playButton.getGlobalBounds().height / 2);
	title.setPosition(SCREEN_WIDTH / 2 - title.getGlobalBounds().width / 2, title.getGlobalBounds().height * 0.1f);	
}

/**
* @fn Draw
* @brief Draw all the elements of the state
* @param dt : Delta time
*/
void MainMenuState::Draw(float dt)
{
	_data->m_window.clear();

	_data->m_window.draw(_background);
	_MainMenuUi->draw(_data->m_window);

	//_data->m_window.draw(playButton);
	_data->m_window.draw(title);

	_data->m_window.display();
}

/**
* @fn LoadTextures
* @brief Load all the textures of the state  
*/
void MainMenuState::LoadTextures()
{
	_data->m_assetManager.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	_data->m_assetManager.LoadTexture("Game Title", MAIN_MENU_TITLE_PATH);
	_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	_data->m_assetManager.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
}

/**
* @fn SetTextures
* @brief Set all the textures of the state
*/
void MainMenuState::SetTextures()
{
	_background.setTexture(_data->m_assetManager.GetTexture("Main Menu Background"));
	title.setTexture(_data->m_assetManager.GetTexture("Game Title"));
	playButton.setTexture(_data->m_assetManager.GetTexture("Play Button"));
}