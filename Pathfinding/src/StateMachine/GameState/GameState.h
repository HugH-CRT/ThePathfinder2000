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

	void InitGridTiles();
	void PlacePiece(sf::Mouse::Button);

	void ResetStartPoint(int column, int row);
	void ResetEndPoint(int column, int row);
	void ResetWall(int column, int row);
	

	void PlaceStartPoint(int column, int row);
	void PlaceEndPoint(int column, int row);
	void PlaceWall(int column, int row);
	
	GameDataRef _data;

	bool StartPlaced;
	bool EndPlaced;

	sf::Vector2i startingPoint;
	sf::Vector2i endingPoint;

	sf::Sprite _background;
	sf::Sprite _pauseButton;
	sf::Sprite _gridSprite;
	sf::Sprite _gridPieces[3][3];
	int _gridArray[3][3];
};

#endif /* GAME_STATE_H */