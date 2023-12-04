/**
* @file GameState.h
*
* @brief Game screen of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Game.h"
#include "defined.h"

#include <SFML/Graphics.hpp>
#include <memory>

/**
* @enum GridPieces
* @brief Enum of the grid pieces
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

/**
* @class GameState
* @brief
*/
class GameState final : public State
{

public:
	// GameState();
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

	void PauseGame();
	void Start();
	void ClearAll();
	void ClearPath();
	void DiagonalMode();
	void DebugMode();
	void ForwardDebug();
	void BackwardDebug();

private : 

	GameDataRef _data;
	std::unique_ptr<class UIWidget> _gameWidget;

#pragma region Sprites 

	sf::Sprite _gridPieces[NB_LINES][NB_COLUMNS];
	sf::Sprite _gridSprite;
	sf::Sprite _portal;

#pragma endregion Sprites

	void InitGridTiles();
	void PlaceItem(int column, int row, const std::string& textureName, GridPieces itemType, std::vector<sf::Vector2i>* itemContainer);
	void ResetItem(int column, int row, GridPieces resetType, std::vector<sf::Vector2i>* itemContainer);
	
	void PlacePiece(GridPieces);
};

#endif /* GAME_STATE_H */