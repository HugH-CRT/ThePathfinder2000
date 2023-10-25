#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class SplashState : public State
{
public:
	explicit SplashState(GameDataRef data);

	/* Implementation of State class */
	
	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;
	void LoadTextures() override;
	void SetTextures() override;

	/* Implementation of State class */

private: 
	GameDataRef m_data;

	sf::Clock m_clock;

	sf::Sprite m_background;
};

#endif /* SPLASH_STATE_H */ 
