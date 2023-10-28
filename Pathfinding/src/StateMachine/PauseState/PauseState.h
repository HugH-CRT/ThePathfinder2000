/**
* @file PauseState.h
 *
 * @brief Pause screen of the game
 *
 * @author yoan.laurain@ynov.com
 *
 */

#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

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
	
	/* Implementation of State class */

private:

	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _resumeButton;
	sf::Sprite _homeButton;
};

#endif /* PAUSE_STATE_H */