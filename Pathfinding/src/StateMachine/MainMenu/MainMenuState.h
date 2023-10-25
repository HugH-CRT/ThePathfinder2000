#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class MainMenuState : public State
{
public: 
	explicit MainMenuState(GameDataRef data);

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
	sf::Sprite playButton;
	sf::Sprite title;
};
#endif /* MAIN_MENU_STATE_H */