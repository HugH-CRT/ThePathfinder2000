#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Game.h"
#include "../defined.h"

#include <SFML/Graphics.hpp>

enum GridPieces
{
	EMPTY_PIECE = 0,
	START_PIECE = 1,
	END_PIECE = 2,
	WALL_PIECE = 3,
	PATH_PIECE = 4,
	CHECKPOINT_PIECE = 5
};

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
	void PlacePiece(GridPieces);

	void Play();
	void SortCheckpointsByDistance(std::vector<sf::Vector2i>& checkpoints, const sf::Vector2i& fromPoint);
	sf::Vector2i ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, const sf::Vector2i& currentPoint);
	void ProcessFinalPath(const sf::Vector2i& currentPoint);
	float CalculateDistance(const sf::Vector2i& point1, const sf::Vector2i& point2);
	bool CheckMapValidity();

	void ResetStartPoint(int column, int row);
	void ResetEndPoint(int column, int row);
	void ResetWall(int column, int row);	
	void ResetCheckPoint(int column, int row);

	void PlaceStartPoint(int column, int row);
	void PlaceEndPoint(int column, int row);
	void PlaceWall(int column, int row);
	void PlaceCheckPoint(int column, int row);

	void DrawPath(stack<Pair> Path);

	void ClearPath();
	
	GameDataRef _data;

	bool StartPlaced;
	bool EndPlaced;
	bool UseDiagonal;

	sf::Vector2i LastCellChanged;

	std::vector<sf::Vector2i> CheckPoints;

	sf::Vector2i startingPoint;
	sf::Vector2i endingPoint;

	sf::Sprite _background;
	sf::Sprite _pauseButton;
	sf::Sprite _gridSprite;
	sf::Sprite _playButton;
	sf::Sprite _checkBox;

	sf::Text _checkBoxText;
	
	sf::Sprite _gridPieces[NB_LINES][NB_COLUMNS];
	int _gridArray[NB_LINES][NB_COLUMNS];
};

#endif /* GAME_STATE_H */