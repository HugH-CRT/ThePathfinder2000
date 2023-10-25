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
	CHECKPOINT_PIECE = 5,
	PORTAL_PIECE = 6
};

class GameState : public State
{

public:
	GameState(GameDataRef data);
	
	/* Implementation of State class */
	
	void Draw(float dt) override;
	void HandleInput() override;
	void Init() override;
	void LoadTextures() override;
	void SetTextures() override;
	void Update(float dt) override;
	
	/* Implementation of State class */

	void DrawStepPath(Pair step, bool isPath);

private : 

	GameDataRef _data;

#pragma region Sprites 

	sf::Sprite m_background;
	sf::Sprite m_backwardDebug;
	sf::Sprite m_checkBoxDebugMode;
	sf::Sprite m_checkBoxDiagMode;
	sf::Sprite m_forwardDebug;
	sf::Sprite m_gridPieces[NB_LINES][NB_COLUMNS];
	sf::Sprite m_gridSprite;
	sf::Sprite m_pauseButton;
	sf::Sprite m_playButton;
	sf::Sprite m_portal;

#pragma endregion Sprites
	
#pragma region Texts 

	sf::Text m_checkBoxDebugText;
	sf::Text m_checkBoxDiagText;
	
#pragma endregion Texts

	void InitGridTiles();
	void ClearPath();
	void PlaceItem(int column, int row, const std::string& textureName, GridPieces itemType, std::vector<sf::Vector2i>* itemContainer);
	void ResetItem(int column, int row, const std::string& resetTexture, GridPieces resetType, std::vector<sf::Vector2i>* itemContainer);
	
	void PlacePiece(GridPieces);
};

#endif /* GAME_STATE_H */