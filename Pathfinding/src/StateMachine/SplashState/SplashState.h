/**
* @file SplashState.h
 *
 * @brief Splash screen of the game
 *
 * @author yoan.laurain@ynov.com
 *
 */

#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class SplashState final : public State
{
public:
	explicit SplashState(GameDataRef data);

	/* Implementation of State class */
	
	void Draw(float dt) override;
	void HandleInput() override;
	void Init() override;
	void LoadTextures() override;
	void LoadFonts() override {}
	void SetTexts() override{}
	void SetTextures() override;
	void Update(float dt) override;
	void SetScales() override;
	void SetPositions() override {};

	/* Implementation of State class */

private: 
	GameDataRef m_data;

	sf::Clock m_clock;

	sf::Sprite m_background;
};

#endif /* SPLASH_STATE_H */ 