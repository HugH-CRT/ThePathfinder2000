#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "../StateMachine/State.h"
#include "../core/Game.h"

#include <SFML/Graphics.hpp>

class SplashState : public State
{
	public :
		SplashState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private : 
		GameDataRef m_data;

		sf::Clock m_clock;

		sf::Sprite m_background;
};

#endif /* SPLASH_STATE_H */ 