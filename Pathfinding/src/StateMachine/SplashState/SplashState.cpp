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
#include "Widget/UIWidget.h"
#include "Widget/SplashWidget/SplashWidget.h"

/**
* @fn SplashState
* @brief Constructor of the SplashState class
* @param data : shared pointer on the game data
*/
SplashState::SplashState(GameDataRef data) 
	: m_data(std::move(data))
{
}

SplashState::~SplashState() = default;

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

	_slashWidget = std::make_unique<SplashWidget>(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)), m_data);
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
* @param dt : delta time
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
}

/**
* @fn Draw
* @brief Draw the elements of the state 
* @param dt : delta time
*/
void SplashState::Draw(float dt)
{
	m_data->m_window.clear();

	_slashWidget->Draw(m_data->m_window);
	
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
}