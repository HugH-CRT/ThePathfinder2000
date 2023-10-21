#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{

public:
	GameState(GameDataRef data);
	
	void Init();
	
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private : 
	
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _pauseButton;
};

#endif /* GAME_STATE_H */