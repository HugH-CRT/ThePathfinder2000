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
#include "macro.h"
#include "UI/Widget/MainMenuWidget.h"
#include "SFML/System/Vector2.hpp"
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
	DELETE_PTR(_MainMenuWidget);
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
	
	_MainMenuWidget = new MainMenuWidget(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)), _data);
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

		_MainMenuWidget->HandleEvents(event, _data->m_window);
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
}

/**
* @fn SetPositions
* @brief  
*/
void MainMenuState::SetPositions()
{
}

/**
* @fn Draw
* @brief Draw all the elements of the state
* @param dt : Delta time
*/
void MainMenuState::Draw(float dt)
{
	_data->m_window.clear();

	_MainMenuWidget->Draw(_data->m_window);

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
}