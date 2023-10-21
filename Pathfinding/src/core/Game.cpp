#include "Game.h"
#include "../SplashState.h"

Game::Game(int width, int height, std::string title) 
{
	m_data->m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	m_data->machine.AddState(StateRef(new SplashState(this->m_data)));
	Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = m_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (m_data->m_window.isOpen())
	{
		m_data->machine.ProcessStateChanges();
		newTime = m_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= frameRate)
		{
			this->m_data->machine.GetActiveState()->HandleInput();
			this->m_data->machine.GetActiveState()->Update(frameRate);	

			accumulator -= frameRate;
		}

		interpolation = accumulator / frameRate;
		this->m_data->machine.GetActiveState()->Draw(interpolation);
	}
}
