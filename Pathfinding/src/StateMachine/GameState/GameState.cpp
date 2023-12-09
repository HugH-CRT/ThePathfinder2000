/**
* @file GameState.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
* 
* @copyright 
* @version 1.0.0
* @date 28/10/2023
*/

#include "GameState.h"
#include "defined.h"
#include "PauseState/PauseState.h"
#include "Game.h"
#include "UI/Widget/GameWidget.h"

GameState::GameState() = default;

/**
* @fn GameState
* @brief Constructor
* @param data : Game data reference
*/
GameState::GameState(GameDataRef data) 
	: _data(std::move(data)) 
{
	
}

/**
* @fn Init
* @brief  Initialize the state
 *		- Load & set the textures & set scale & position	
*/
void GameState::Init()
{
	LoadTextures();
	SetTextures();
	LoadFonts();
	SetScales();
	SetTexts();
	SetPositions();
	InitGridTiles();

	_gameWidget = std::make_unique<GameWidget>(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)), _data);
}

/**
* @fn HandleInput
* @brief Handle the input of the user 
*/
void GameState::HandleInput()
{
	sf::Event event{};

	while (_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->m_window.close();
		}

		_gameWidget->HandleEvents(event, _data->m_window);

		_data->m_inputManager.HandleKeyDown(event,_gridSprite, *this);
	}
}

/**
* @fn Update
* @brief Update the state
* @param dt : Delta time
*/
void GameState::Update(float dt)
{
}

/**
* @fn SetScales
* @brief Set the scale of the sprites 
*/
void GameState::SetScales()
{
}

/**
* @fn SetPositions
* @brief Set the position of the sprites
*/
void GameState::SetPositions()
{
	_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2,
	                        SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);
}

/**
* @fn Draw
* @brief  Draw the sprites
* @param dt : Delta time
*/
void GameState::Draw(float dt)
{
	_data->m_window.clear();

	_gameWidget->Draw(_data->m_window);

	_data->m_window.draw(_gridSprite);

	for (const auto& m_gridPiece : _gridPieces)
	{
		for (const auto& y : m_gridPiece)
		{
			_data->m_window.draw(y);
		}
	}
	
	_data->m_window.display();
}

/**
* @fn LoadTextures
* @brief Load the textures
*/
void GameState::LoadTextures()
{
	_data->m_assetManager.LoadTexture("Pause Button", PAUSE_BUTTON);
	_data->m_assetManager.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	_data->m_assetManager.LoadTexture("Grid Sprite", EMPTY_TILE);
	_data->m_assetManager.LoadTexture("Wall", WALL);
	_data->m_assetManager.LoadTexture("Path", PATH);
	_data->m_assetManager.LoadTexture("Start Point", START_POINT);
	_data->m_assetManager.LoadTexture("End Point", END_POINT);
	_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	_data->m_assetManager.LoadTexture("Check Box Checked", CHECK_BOX_CHECKED);
	_data->m_assetManager.LoadTexture("Check Box Unchecked", CHECK_BOX_UNCHECKED);
	_data->m_assetManager.LoadTexture("CheckPoint", CHECKPOINT);
	_data->m_assetManager.LoadTexture("Portal", PORTAL);
	_data->m_assetManager.LoadTexture("Forward Arrow", FORWARD_ARROW);
	_data->m_assetManager.LoadTexture("Backward Arrow", BACKWARD_ARROW);
	_data->m_assetManager.LoadTexture("Clear Button", CLEAR_BUTTON);
	_data->m_assetManager.LoadTexture("Clear Path Button", CLEAR_PATH_BUTTON);
}

/**
* @fn LoadFonts
* @brief Load the fonts
*/
void GameState::LoadFonts()
{
	_data->m_assetManager.LoadFont("Robotto Font", FONT); 
}

/**
* @fn SetTexts
* @brief Set all of the texts
*/
void GameState::SetTexts()
{
}

/**
* @fn SetTextures
* @brief Set all of the textures
*/
void GameState::SetTextures()
{
	_gridSprite.setTexture(_data->m_assetManager.GetTexture("Path"));
}

/**
* @fn InitGridTiles
* @brief  Initialize the grid tiles with the empty texture
*         Initialize the grid array with the empty piece
*/
void GameState::InitGridTiles()
{
	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; ++y)
		{
			const float factor = 1.f / NB_COLUMNS;

			_gridPieces[x][y].setScale(factor, factor);
			_gridPieces[x][y].setTexture(_data->m_assetManager.GetTexture("Grid Sprite"));

			const float positionX = _gridSprite.getPosition().x + ( x * _gridPieces[x][y].getGlobalBounds().width ) + x;
			const float positionY = _gridSprite.getPosition().y + ( y * _gridPieces[x][y].getGlobalBounds().height)+ y;

			_gridPieces[x][y].setPosition(positionX,positionY);
			
			GetGame()->SetGridArrayItem(x, y, EMPTY_PIECE); 
		}
	}
}

/**
* @fn PlaceItem
* @brief Place an item on the grid
* @param column : Column of the grid
* @param row : Row of the grid
* @param textureName : Name of the texture to place
* @param itemType : Type of the item to place
* @param itemContainer : Container to update with the new item if needed
*/
void GameState::PlaceItem(const int column, const int row, const std::string& textureName, GridPieces itemType, std::vector<sf::Vector2i>* itemContainer = nullptr)
{
	_gridPieces[column - 1][row - 1].setTexture(_data->m_assetManager.GetTexture(textureName));
	GetGame()->GetGridArray()[column - 1][row - 1] = itemType;

	if (itemContainer) {
		itemContainer->push_back(sf::Vector2i(column - 1, row - 1));
	}

	sf::Vector2i point(column - 1, row - 1);
	
	if (itemType == START_PIECE) {
		GetGame()->_StartingPoint = point;
	}
	else if (itemType == END_PIECE) {
		GetGame()->_EndingPoint = point;
	}

	ClearPath();
}

/** 
* @fn ResetItem
* @brief Reset an item on the grid
* @param column : Column of the grid
* @param row : Row of the grid
* @param resetType : Type of the item that was previously placed
* @param itemContainer : Container of the item to update if needed
*/
void GameState::ResetItem(const int column, const int row, const GridPieces resetType, std::vector<sf::Vector2i>* itemContainer)
{
	// Reset the texture of the item & the grid array value
	_gridPieces[column - 1][row - 1].setTexture(_data->m_assetManager.GetTexture("Grid Sprite"));
	GetGame()->GetGridArray()[column - 1][row - 1] = EMPTY_PIECE;

	// Remove the item from the container
	if (itemContainer) {
		for (int i = 0; i < itemContainer->size(); i++) {
			if (itemContainer->at(i).x == column - 1 && itemContainer->at(i).y == row - 1) {
				itemContainer->erase(itemContainer->begin() + i);
				break;
			}
		}
	}

	// Reset the starting / ending point if needed
	sf::Vector2i point(- 1, - 1);

	if (resetType == START_PIECE) {
		GetGame()->_StartingPoint = point;
	}
	else if (resetType == END_PIECE) {
		GetGame()->_EndingPoint = point;
	}

	if (!GetGame()->_path.empty())
	{
		ClearPath(); 
	}
}

/**
* @fn DrawStepPath
* @brief Draw the current step of the path  
* @param step : Current step of the path
* @param isPath : True is we draw the path, false if we draw empty tiles ( use with forward / backward debug )
*/
void GameState::DrawStepPath(const Pair step, const bool isPath)
{
	// Prevent from overriding over start end or other items
	if ( GetGame()->GetGridArray()[step.first][step.second] ==  EMPTY_PIECE || GetGame()->GetGridArray()[step.first][step.second] == PATH_PIECE )
	{
		_gridPieces[step.first][step.second].setTexture(_data->m_assetManager.GetTexture(isPath ? "Path" : "Grid Sprite"));
		GetGame()->GetGridArray()[step.first][step.second] = PATH_PIECE;
	}
}

/**
 * @fn PauseGame
 * @brief Pause the game
 */
void GameState::PauseGame()
{
	_data->machine.AddState(std::make_unique<PauseState>(_data), false);
}

/**
 * @fn Start
 * @brief Start the game, clear the path & play the game
 */
void GameState::Start()
{
	ClearPath();
	GetGame()->Play();
}

/**
 * @fn ClearAll
 * @brief  Clear the grid with the empty texture & reset the grid array value
 */
void GameState::ClearAll()
{
	GetGame()->ResetGame();
	InitGridTiles();
}

/**
* @fn ClearPath
* @brief Clear the path with the empty texture & reset the grid array value
*/
void GameState::ClearPath()
{
	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; y++)
		{
			if (GetGame()->GetGridArray()[x][y] == PATH_PIECE)
			{
				GetGame()->GetGridArray()[x][y] = EMPTY_PIECE;
				_gridPieces[x][y].setTexture(_data->m_assetManager.GetTexture("Grid Sprite"));
			}
		}
	}
	GetGame()->ClearPath();
}

/**
 * @fn DiagonalMode
 * @brief Enable / Disable the diagonal mode
 */
void GameState::DiagonalMode()
{
	GetGame()->_UseDiagonal = !GetGame()->_UseDiagonal;
}

/**
 * @fn DebugMode
 * @brief Enable / Disable the debug mode
 */
void GameState::DebugMode()
{
	GetGame()->SetDebugMode(!GetGame()->IsDebugMode());
}

/**
 * @fn ForwardDebug
 * @brief Go to the next step of the debug
 */
void GameState::ForwardDebug()
{
	if (GetGame()->IsDebugMode())
	{
		GetGame()->ForwardDebug();
	}
}

/**
 * @fn BackwardDebug
 * @brief Go to the previous step of the debug
 */
void GameState::BackwardDebug()
{
	if (GetGame()->IsDebugMode())
	{
		GetGame()->BackwardDebug();
	}
}

/**
* @fn PlacePiece
* @brief Place a piece on the grid
* @param Piece
* 
* @todo Refactor this function
*/
void GameState::PlacePiece(const GridPieces Piece)
{
	const sf::Vector2i touchPoint = _data->m_inputManager.GetMousePosition(_data->m_window);

	const sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
	const auto gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

	const auto gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

	int column = 0, row  = 0;

	const float columnWidth = _gridSprite.getGlobalBounds().width / NB_COLUMNS;
	const float rowHeight = _gridSprite.getGlobalBounds().height / NB_LINES; 

	for (int c = 1; c <= NB_COLUMNS; c++) {
		if (gridLocalTouchPos.x < columnWidth * c) {
			column = c;
			break;
		}
	}

	for (int r = 1; r <= NB_LINES; r++) {
		if (gridLocalTouchPos.y < rowHeight * r) {
			row = r;
			break;
		}
	}

	const bool StartPlaced = GetGame()->_StartingPoint.x != -1 && GetGame()->_StartingPoint.y != -1;
	const bool EndPlaced = GetGame()->_EndingPoint.x != -1 && GetGame()->_EndingPoint.y != -1;

	sf::Vector2i point( -1, - 1);

	switch (Piece) {
	case START_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, START_PIECE, nullptr);
			break;
		}
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")  ) {
			ResetItem(column, row, END_PIECE, nullptr);
			GetGame()->_EndingPoint = point;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall") ) {
			ResetItem(column, row, WALL_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, PORTAL_PIECE, GetGame()->_Portals);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, CHECKPOINT_PIECE, GetGame()->_CheckPoints);
		}

		if (!StartPlaced)
		{
			PlaceItem(column, row, "Start Point", START_PIECE,nullptr);
		}

		break;

	case END_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, END_PIECE, nullptr);
			break;
		}
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, START_PIECE, nullptr);
			GetGame()->_StartingPoint = point;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, WALL_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, PORTAL_PIECE, GetGame()->_Portals);

		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, CHECKPOINT_PIECE, GetGame()->_CheckPoints);

		}

		if (!EndPlaced)
		{
			PlaceItem(column, row, "End Point", END_PIECE, nullptr);
		}

		break;

	case WALL_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, END_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, START_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, WALL_PIECE, nullptr);
			break;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, PORTAL_PIECE, GetGame()->_Portals);

		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, CHECKPOINT_PIECE, GetGame()->_CheckPoints);

		}

		PlaceItem(column, row, "Wall", WALL_PIECE, nullptr);
		
		break;

	case CHECKPOINT_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, CHECKPOINT_PIECE, GetGame()->_CheckPoints);

			break;
		}
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, START_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, END_PIECE, nullptr);

		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, WALL_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, PORTAL_PIECE, GetGame()->_Portals);

		}
		
		PlaceItem(column, row, "CheckPoint", CHECKPOINT_PIECE, GetGame()->_CheckPoints);

		break;

	case PORTAL_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, PORTAL_PIECE, GetGame()->_Portals);
			break;
		}
		if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, START_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, END_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, WALL_PIECE, nullptr);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, CHECKPOINT_PIECE, GetGame()->_CheckPoints);
		}

		PlaceItem(column, row, "Portal", PORTAL_PIECE, GetGame()->_Portals);

		break;

	default:
		break;
	}

}

GameDataRef GameState::GetGameData() const
{
	return _data;
}