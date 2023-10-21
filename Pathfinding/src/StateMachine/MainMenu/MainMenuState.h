#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../StateMachine/State.h"
#include "../Game.h"

#include <SFML/Graphics.hpp>

class MainMenuState : public State
{
	public: 
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private : 
		
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite playButton;
		sf::Sprite playButtonOuter;
		sf::Sprite title;

};
#endif /* MAIN_MENU_STATE_H */