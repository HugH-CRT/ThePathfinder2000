/**
* @file GameState.h
 *
 * @brief Game screen of the game
 *
 * @author yoan.laurain@ynov.com
 *
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Game.h"
#include "../defined.h"

#include <SFML/Graphics.hpp>

/*
 *  Brief : Enum of the grid pieces
 */
enum GridPieces
{
	EMPTY_PIECE = 0,
	START_PIECE = 1,
	END_PIECE = 2,
	WALL_PIECE = 3,
	PATH_PIECE = 4,
	CHECKPOINT_PIECE = 5,
	PORTAL_PIECE = 6
};

class GameState final : public State
{

public:
	explicit GameState(GameDataRef data);
	
	/* ImplGameDataRef e class */
	
	void Draw(float dt) override;
	void HandleInput() override;
	void Init() override;
	void LoadTextures() override;
	void LoadFonts() override;
	void SetTexts() override;
	void SetTextures() override;
	void Update(float dt) override;
	void SetScales() override;
	void SetPositions() override;
	
	/* Implementation of State class */

	void DrawStepPath(Pair step, bool isPath);

private : 

	GameDataRef _data;

#pragma region Sprites 

	sf::Sprite _background;
	sf::Sprite _backwardDebug;
	sf::Sprite _checkBoxDebugMode;
	sf::Sprite _checkBoxDiagMode;
	sf::Sprite _forwardDebug;
	sf::Sprite _gridPieces[NB_LINES][NB_COLUMNS];
	sf::Sprite _gridSprite;
	sf::Sprite _pauseButton;
	sf::Sprite _playButton;
	sf::Sprite _portal;

#pragma endregion Sprites
	
#pragma region Texts 

	sf::Text _checkBoxDebugText;
	sf::Text _checkBoxDiagText;
	
#pragma endregion Texts

	void InitGridTiles();
	void ClearPath();
	void PlaceItem(int column, int row, const std::string& textureName, GridPieces itemType, std::vector<sf::Vector2i>* itemContainer);
	void ResetItem(int column, int row, GridPieces resetType, std::vector<sf::Vector2i>* itemContainer);
	
	void PlacePiece(GridPieces);
};

#endif /* GAME_STATE_H */