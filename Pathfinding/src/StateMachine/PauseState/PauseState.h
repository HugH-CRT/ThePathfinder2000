#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class PauseState : public State
{

public:
	PauseState(GameDataRef data);

	/* Implementation of State class */
	
	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;
	void LoadTextures() override;
	void SetTextures() override;
	
	/* Implementation of State class */

private:

	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _resumeButton;
	sf::Sprite _homeButton;
};

#endif /* PAUSE_STATE_H */