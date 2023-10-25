#include "SplashState.h"
#include "defined.h"
#include "MainMenu/MainMenuState.h"

#include <sstream>
#include <iostream>

SplashState::SplashState(GameDataRef data) 
	: m_data(data)
{
}

void SplashState::Init()
{
	LoadTextures();
	SetTextures();
	
	this->m_background.setScale(SCREEN_WIDTH / this->m_background.getLocalBounds().width, SCREEN_HEIGHT / this->m_background.getLocalBounds().height);
}

void SplashState::HandleInput()
{
	sf::Event event{};
	
	while (this->m_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->m_data->m_window.close();
		}
	}
}

void SplashState::Update(float dt)
{
	if (m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		this->m_data->machine.AddState(StateRef(new MainMenuState(m_data)), true);
	}
}

void SplashState::Draw(float dt)
{
	this->m_data->m_window.clear();

	this->m_data->m_window.draw(m_background);
	
	this->m_data->m_window.display();
}

void SplashState::LoadTextures()
{
	this->m_data->m_assetManager.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
}

void SplashState::SetTextures()
{
	m_background.setTexture(m_data->m_assetManager.GetTexture("Splash State Background"));
}