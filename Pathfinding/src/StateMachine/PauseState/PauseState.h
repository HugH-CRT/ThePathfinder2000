/**
* @file PauseState.h
*
* @brief Pause screen of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

/**
* @class PauseState
* @brief
*/
class PauseState final : public State
{

public:
	explicit PauseState(GameDataRef data);

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
	void SetPositions() override;
	
private:

	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _resumeButton;
	sf::Sprite _homeButton;
};

#endif /* PAUSE_STATE_H */