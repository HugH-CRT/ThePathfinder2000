/**
* @file SplashState.cpp
* @brief 
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "SplashState.h"
#include "defined.h"
#include "MainMenu/MainMenuState.h"

/**
* @fn SplashState
* @brief  
* @param data
*/
SplashState::SplashState(GameDataRef data) 
	: m_data(std::move(data))
{
}

/**
* @fn Init
* @brief Initialize the state
*   	 - Load & set the textures 
*/
void SplashState::Init()
{
	LoadTextures();
	SetTextures();
	SetScales();
}

/**
* @fn HandleInput
* @brief Handle the user inputs  
*/
void SplashState::HandleInput()
{
	sf::Event event{};
	
	while (m_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_data->m_window.close();
		}
	}
}

/**
* @fn Update
* @brief Update the state
*	     Switch to the main menu state after a certain time
* @param dt
*/
void SplashState::Update(float dt)
{
	if (m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		m_data->machine.AddState(std::make_unique<MainMenuState>(m_data), true);
	}
}

/**
* @fn SetScales
* @brief Set the scales of the elements of the state 
*/
void SplashState::SetScales()
{
	m_background.setScale(SCREEN_WIDTH / m_background.getLocalBounds().width,
						  SCREEN_HEIGHT / m_background.getLocalBounds().height);
}

/**
* @fn Draw
* @brief Draw the elements of the state 
* @param dt
*/
void SplashState::Draw(float dt)
{
	m_data->m_window.clear();

	m_data->m_window.draw(m_background);
	
	m_data->m_window.display();
}

/**
* @fn LoadTextures
* @brief Load all the textures of the state  
*/
void SplashState::LoadTextures()
{
	m_data->m_assetManager.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
}

/**
* @fn SetTextures
* @brief Set all the textures of the state  
*/
void SplashState::SetTextures()
{
	m_background.setTexture(m_data->m_assetManager.GetTexture("Splash State Background"));
}