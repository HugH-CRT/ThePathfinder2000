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
	~GameState();
	
	/* Implementation of State class */
	
	void Draw(float dt) override;
	void HandleInput() override;
	void Init() override;
	void LoadTextures() override;
	void SetTextures() override;
	void Update(float dt) override;
	
	/* Implementation of State class */

private : 

	GameDataRef m_data;

	/* TODO : A deplacer */
	
	bool m_UseDiagonal;
	bool m_DebugMode;
	
	int m_CurrentDebugStep;
	int _gridArray[NB_LINES][NB_COLUMNS];

	std::vector<sf::Vector2i>* m_CheckPoints;
	std::vector<sf::Vector2i>* m_Portals;

	sf::Vector2i m_StartingPoint;
	sf::Vector2i m_EndingPoint;

	std::vector<Pair> _path;

	/* TODO : A deplacer  */

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
	void DrawStepPath(Pair step, bool isPath);
	void PlaceItem(int column, int row, const std::string& textureName, int itemType, std::vector<sf::Vector2i>* itemContainer);
	void ResetItem(int column, int row, const std::string& resetTexture, int resetType, std::vector<sf::Vector2i>* itemContainer);


	
	void PlacePiece(GridPieces);


	

	void Play();
	sf::Vector2i ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, sf::Vector2i& currentPoint);
	void ProcessFinalPath(sf::Vector2i& currentPoint);
	bool CheckMapValidity();

	void CheckPortalPath(sf::Vector2i& currentPoint, sf::Vector2i& nextPoint, std::vector<Pair> basePath);

	sf::Vector2i& GetClosestPortal(sf::Vector2i& point);

	void ForwardDebug();
	void BackwardDebug();
};

#endif /* GAME_STATE_H */