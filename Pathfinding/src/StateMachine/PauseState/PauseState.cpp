#include "PauseState.h"
#include "defined.h"
#include "GameState/GameState.h"
#include "MainMenu/MainMenuState.h"

#include <sstream>

PauseState::PauseState(GameDataRef data) 
	: _data(std::move(data))
{
}

/*
 * Brief : Initialize the state
 *		- Load & set the textures & set scale & position	
 */
void PauseState::Init()
{
	LoadTextures();
	SetTextures();
	SetScales();
	SetPositions();
}

/*
 * Brief : Handle the user inputs
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
		
		// Resume button
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->
			m_inputManager.IsMouseOverSprite(_resumeButton, _data->m_window))
		{
			_data->machine.RemoveState();
		}

		// Home button
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->
			m_inputManager.IsMouseOverSprite(_homeButton, _data->m_window))
		{
			_data->machine.RemoveState();
			_data->machine.AddState(std::make_unique<MainMenuState>(_data), true);
		}
	}
}

void PauseState::Update(float dt)
{
}

/*
 * Brief : Set the scale of the elements
 */
void PauseState::SetScales()
{
	_resumeButton.setScale(0.1f, 0.1f);
	_homeButton.setScale(0.1f, 0.1f);
	_background.setScale(SCREEN_WIDTH / _background.getGlobalBounds().width,
						 SCREEN_HEIGHT / _background.getGlobalBounds().height);	
}

/*
 * Brief : Set the position of the elements
 */
void PauseState::SetPositions()
{
	_resumeButton.setPosition(SCREEN_WIDTH / 2 - _resumeButton.getGlobalBounds().width / 2,
							  SCREEN_HEIGHT / 3 - _resumeButton.getGlobalBounds().height / 2);
	
	_homeButton.setPosition(SCREEN_WIDTH / 2 - _homeButton.getGlobalBounds().width / 2,
							SCREEN_HEIGHT / 3 * 2 - _homeButton.getGlobalBounds().height / 2);
}

/*
 * Brief : Draw all the elements of the state
 *
 * @param dt : Delta time
 */
void PauseState::Draw(float dt)
{
	_data->m_window.clear();

	_data->m_window.draw(_background);
	_data->m_window.draw(_resumeButton);
	_data->m_window.draw(_homeButton);

	_data->m_window.display();
}

/*
 * Brief : Load all the textures of the state
 */
void PauseState::LoadTextures()
{
	_data->m_assetManager.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
	_data->m_assetManager.LoadTexture("Resume Button", RESUME_BUTTON);
	_data->m_assetManager.LoadTexture("Home Button", HOME_BUTTON);
}

/*
 * Brief : Set all the textures of the state
 */
void PauseState::SetTextures()
{
	_background.setTexture(_data->m_assetManager.GetTexture("Pause Background"));
	_resumeButton.setTexture(_data->m_assetManager.GetTexture("Resume Button"));
	_homeButton.setTexture(_data->m_assetManager.GetTexture("Home Button"));
}