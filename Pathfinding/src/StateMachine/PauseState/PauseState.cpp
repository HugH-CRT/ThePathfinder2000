/**
* @file PauseState.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "PauseState.h"
#include "defined.h"
#include "GameState/GameState.h"
#include "MainMenu/MainMenuState.h"
#include "Widget/PauseWidget/PauseWidget.h"

/**
* @fn PauseState
* @brief  
* @param data
*/
PauseState::PauseState(GameDataRef data) 
	: _data(std::move(data))
{
}

/**
* @fn Init
* @brief Initialize the state
*        - Load & set the textures & set scale & position	  
*/
void PauseState::Init()
{
	LoadTextures();
	SetTextures();
	SetScales();
	SetPositions();

	_pauseWidget = std::make_unique<PauseWidget>(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)), _data);
}

/**
* @fn HandleInput
* @brief Handle the user inputs  
*/
void PauseState::HandleInput()
{
	sf::Event event{};

	while (_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->m_window.close();
		}

		_pauseWidget->HandleEvents(event, _data->m_window);
	}
}

/**
* @fn Update
* @brief  
* @param dt
*/
void PauseState::Update(float dt)
{
}

/**
* @fn SetScales
* @brief Set the scale of the elements
*/
void PauseState::SetScales()
{
}

/**
* @fn SetPositions
* @brief Set the position of the elements
*/
void PauseState::SetPositions()
{
}

void PauseState::ResumeState()
{
	_data->machine.RemoveState();
}

void PauseState::BackToHome()
{
	_data->machine.RemoveState();
	_data->machine.AddState(std::make_unique<MainMenuState>(_data), true);
}

/**
* @fn Draw
* @brief Draw all the elements of the state
* @param dt : Delta time
*/
void PauseState::Draw(float dt)
{
	_data->m_window.clear();

	_pauseWidget->Draw(_data->m_window);

	_data->m_window.display();
}

/**
* @fn LoadTextures
* @brief Load all the textures of the state
*/
void PauseState::LoadTextures()
{
	_data->m_assetManager.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
	_data->m_assetManager.LoadTexture("Resume Button", RESUME_BUTTON);
	_data->m_assetManager.LoadTexture("Home Button", HOME_BUTTON);
}

/**
* @fn SetTextures
* @brief Set all the textures of the state 
*/
void PauseState::SetTextures()
{
}