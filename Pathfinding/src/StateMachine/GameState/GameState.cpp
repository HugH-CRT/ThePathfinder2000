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
#include "Widget/GameWidget/GameWidget.h"

// GameState::GameState() = default;

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
	_data->m_assetManager.LoadTexture("Resume Button", RESUME_BUTTON);
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
* @brief Place a game piece on the grid based on the user's input.
* @param piece : The type of game piece to place.
*/
void GameState::PlacePiece(const GridPieces piece)
{
    // Get the mouse position in the game window
    const sf::Vector2i touchPoint = _data->m_inputManager.GetMousePosition(_data->m_window);
    const sf::FloatRect gridSize = _gridSprite.getGlobalBounds();

    // Calculate the gap outside of the grid
    const auto gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

    // Calculate the local touch position within the grid
    const auto gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

    // Determine the column and row based on the touch position
    int column = GetColumnFromPosition(gridLocalTouchPos.x);
    int row = GetRowFromPosition(gridLocalTouchPos.y);

    // Information about different types of game pieces
    const std::vector<PieceInfo> pieceInfos =
	{
        PieceInfo{"Start Point", START_PIECE, &GetGame()->_StartingPoint, nullptr},
        PieceInfo{"End Point", END_PIECE, &GetGame()->_EndingPoint, nullptr},
        PieceInfo{"Wall", WALL_PIECE, nullptr, nullptr},
        PieceInfo{"Portal", PORTAL_PIECE, nullptr, GetGame()->_Portals},
        PieceInfo{"CheckPoint", CHECKPOINT_PIECE, nullptr, GetGame()->_CheckPoints} 
    };

    // Check if the clicked position already has a piece and reset it
    for (const auto& info : pieceInfos) {
        if (_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture(info.textureName)) {
            ResetItem(column, row, info.type, info.container);
            if (info.type == START_PIECE || info.type == END_PIECE) {
                break;
            }
        }
    }

    // Place the new piece if the position is valid and no piece is already there
    for (const auto& info : pieceInfos) {
        if (piece == info.type && !IsPiecePlaced(info.type, column, row)) {
            PlaceItem(column, row, info.textureName, info.type, info.container);
            break;
        }
    }
}

/**
* @fn GetColumnFromPosition
* @brief Gets the column index on the grid based on the given x-coordinate position.
* @param xPosition : The x-coordinate position.
* @return The column index.
*/
int GameState::GetColumnFromPosition(float xPosition) const
{
	const float columnWidth = _gridSprite.getGlobalBounds().width / NB_COLUMNS;
    
	// Calculate and return the column index
	return static_cast<int>(xPosition / columnWidth) + 1;
}

/**
* @fn GetRowFromPosition
* @brief Gets the row index on the grid based on the given y-coordinate position.
* @param yPosition : The y-coordinate position.
* @return The row index.
*/
int GameState::GetRowFromPosition(float yPosition) const
{
	const float rowHeight = _gridSprite.getGlobalBounds().height / NB_LINES;
    
	// Calculate and return the row index
	return static_cast<int>(yPosition / rowHeight) + 1;
}

/**
* @fn IsPiecePlaced
* @brief Checks if a specific game piece is already placed on the grid at the given position.
* @param pieceType : The type of game piece to check.
* @param column : The column on the grid.
* @param row : The row on the grid.
* @return True if the piece is already placed, false otherwise.
*/
bool GameState::IsPiecePlaced(GridPieces pieceType, int column, int row) const
{
	const auto& gridArray = GetGame()->GetGridArray();

	// Check if the piece is the starting point
	if (pieceType == START_PIECE)
	{
		return GetGame()->_StartingPoint.x != -1 && GetGame()->_StartingPoint.y != -1;
	}

	// Check if the piece is the ending point
	if (pieceType == END_PIECE)
	{
		return GetGame()->_EndingPoint.x != -1 && GetGame()->_EndingPoint.y != -1;
	}

	// Check if the column and row are within valid bounds
	if (column > 0 && row > 0 && column <= NB_COLUMNS && row <= NB_LINES)
	{
		// Check if the specified piece is placed at the given position on the grid
		return gridArray[column - 1][row - 1] == pieceType;
	}

	// Default case: the piece is not placed
	return false;
}

GameDataRef GameState::GetGameData() const
{
	return _data;
}