/**
* @file SplashState.h
*
* @brief Splash screen of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "State.h"
#include "Game.h"

/**
* @class SplashState
* @brief
*/
class SplashState final : public State
{
public:
	explicit SplashState(GameDataRef data);
	~SplashState() override;

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

private: 
	GameDataRef m_data;

	sf::Clock m_clock;

	std::unique_ptr<class UIWidget> _slashWidget;
};

#endif /* SPLASH_STATE_H */ 