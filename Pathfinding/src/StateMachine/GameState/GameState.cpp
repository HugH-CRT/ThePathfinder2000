#include "GameState.h"
#include "../defined.h"
#include "../PauseState/PauseState.h"
#include "Game.h"

#include <sstream>

GameState::GameState(GameDataRef data) 
	: _data(std::move(data)) 
{
	
}

/*
 * Brief : Initialize the state
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
}

/*
 * Brief : Handle the input of the user
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

		// Pause the game
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code &&_data->m_inputManager.IsMouseOverSprite( _pauseButton, _data->m_window))
		{
			_data->machine.AddState(std::make_unique<PauseState>(_data), false);
		}

		// Left click to place the start point
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(_gridSprite, _data->m_window))
		{
			PlacePiece(START_PIECE);
		}

		// Right click to place the end point
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Right == event.key.code && _data->m_inputManager.IsMouseOverSprite(_gridSprite, _data->m_window))
		{
			PlacePiece(END_PIECE);
		}

		// Press W to place a wall
		if (sf::Event::KeyReleased == event.type && sf::Keyboard::W == event.key.code)
		{
			if (_data->m_inputManager.IsMouseOverSprite(_gridSprite, _data->m_window))
			{
				PlacePiece(WALL_PIECE);
			}
		}

		// Press C to place a checkpoint
		if (sf::Event::KeyReleased == event.type && sf::Keyboard::C == event.key.code)
		{
			if (_data->m_inputManager.IsMouseOverSprite(this->_gridSprite, _data->m_window))
			{
				PlacePiece(CHECKPOINT_PIECE);
			}
		}

		// Press P to place a portal
		if (sf::Event::KeyReleased == event.type && sf::Keyboard::P == event.key.code)
		{
			if (_data->m_inputManager.IsMouseOverSprite(_gridSprite, _data->m_window))
			{
				PlacePiece(PORTAL_PIECE);
			}
		}

		// Click on play button to start the game
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(_playButton, _data->m_window))
		{
			ClearPath();
			GetGame()->Play();
		}

		// Check / uncheck the diagonal mode
		if (_data->m_inputManager.IsSpriteClicked(_checkBoxDiagMode, sf::Mouse::Left, _data->m_window))
		{
			GetGame()->_UseDiagonal = !GetGame()->_UseDiagonal;
			_checkBoxDiagMode.setTexture(_data->m_assetManager.GetTexture(GetGame()->_UseDiagonal ? "Check Box Checked" : "Check Box Unchecked"));
		}

		// Check / uncheck the debug mode
		if (_data->m_inputManager.IsSpriteClicked(_checkBoxDebugMode, sf::Mouse::Left, _data->m_window))
		{
			GetGame()->SetDebugMode(!GetGame()->IsDebugMode());
			_checkBoxDebugMode.setTexture(_data->m_assetManager.GetTexture(GetGame()->IsDebugMode() ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (GetGame()->IsDebugMode())
		{
			// Click on the forward arrow to go to the next step
			if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(_forwardDebug, _data->m_window))
			{
				GetGame()->ForwardDebug();
			}

			// Click on the backward arrow to go to the previous step
			if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(_backwardDebug, _data->m_window))
			{
				GetGame()->BackwardDebug();
			}
		}

		// clear button
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(_clearButton, _data->m_window))
		{
			GetGame()->ResetGame();
			InitGridTiles();
		}

		// clear path button
		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(_clearPathButton, _data->m_window))
		{
			ClearPath();
		}
	}
}

void GameState::Update(float dt)
{
}

/*
 * Brief : Set the scale of the sprites
 */
void GameState::SetScales()
{
	_background.setScale(SCREEN_WIDTH / _background.getLocalBounds().width,
	                     SCREEN_HEIGHT / _background.getLocalBounds().height);
	_pauseButton.setScale(0.3f, 0.3f);
	_playButton.setScale(0.3f, 0.3f);
	_checkBoxDiagMode.setScale(0.1f, 0.1f);
	_checkBoxDebugMode.setScale(0.1f, 0.1f);
	
	_backwardDebug.setScale(0.5f, 0.5f);
	_forwardDebug.setScale(0.5f, 0.5f);
	_clearButton.setScale(0.5f, 0.5f);
	_clearPathButton.setScale(0.5f, 0.5f);
}

/*
 * Brief : Set the position of the sprites
 */
void GameState::SetPositions()
{
	_pauseButton.setPosition(SCREEN_WIDTH - _pauseButton.getGlobalBounds().width, _pauseButton.getPosition().y);
	_playButton.setPosition(_playButton.getGlobalBounds().width, _playButton.getPosition().y);
	
	_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2,
	                        SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);
	
	_checkBoxDiagMode.setPosition(SCREEN_WIDTH / 4 - _checkBoxDiagMode.getGlobalBounds().width,
	                              SCREEN_HEIGHT / 2 - _checkBoxDiagMode.getGlobalBounds().height);
	
	_checkBoxDiagText.setPosition(
		SCREEN_WIDTH / 4 - _checkBoxDiagText.getGlobalBounds().width - _checkBoxDiagMode.getGlobalBounds().width * 2,
		SCREEN_HEIGHT / 2 - _checkBoxDiagMode.getGlobalBounds().height);
	
	_checkBoxDebugMode.setPosition(SCREEN_WIDTH / 4 - _checkBoxDebugMode.getGlobalBounds().width,
	                               SCREEN_HEIGHT / 2 - _checkBoxDebugMode.getGlobalBounds().height - _checkBoxDiagMode.
	                               getGlobalBounds().height);
	
	_checkBoxDebugText.setPosition(
		SCREEN_WIDTH / 4 - _checkBoxDebugText.getGlobalBounds().width - _checkBoxDebugMode.getGlobalBounds().width * 2,
		SCREEN_HEIGHT / 2 - _checkBoxDebugMode.getGlobalBounds().height - _checkBoxDiagMode.getGlobalBounds().height);
	
	_backwardDebug.setPosition(SCREEN_WIDTH / 2 - _backwardDebug.getGlobalBounds().width / 2,
	                           SCREEN_HEIGHT - _backwardDebug.getGlobalBounds().height);
	
	_forwardDebug.setPosition(SCREEN_WIDTH / 2 + _forwardDebug.getGlobalBounds().width / 2,
	                          SCREEN_HEIGHT - _forwardDebug.getGlobalBounds().height);

	_clearButton.setPosition(SCREEN_WIDTH / 2 - _clearButton.getGlobalBounds().width / 2,
							_clearButton.getGlobalBounds().height / 2);

	_clearPathButton.setPosition(SCREEN_WIDTH / 2 + _clearButton.getGlobalBounds().width + _clearPathButton.getGlobalBounds().width / 2,
								_clearPathButton.getGlobalBounds().height / 2);
}

/*
 * Brief : Draw the sprites
 *
 * @param dt : Delta time
 */
void GameState::Draw(float dt)
{
	_data->m_window.clear();
	
	_data->m_window.draw(_background);
	_data->m_window.draw(_gridSprite);
	_data->m_window.draw(_playButton);
	_data->m_window.draw(_checkBoxDiagText);
	_data->m_window.draw(_forwardDebug);
	_data->m_window.draw(_backwardDebug);
	_data->m_window.draw(_checkBoxDebugText);
	_data->m_window.draw(_checkBoxDebugMode);
	_data->m_window.draw(_pauseButton);
	_data->m_window.draw(_checkBoxDiagMode);
	_data->m_window.draw(_clearButton);
	_data->m_window.draw(_clearPathButton);

	for (const auto& m_gridPiece : _gridPieces)
	{
		for (const auto& y : m_gridPiece)
		{
			_data->m_window.draw(y);
		}
	}
	
	_data->m_window.display();
}

/*
 * Brief : Load the textures
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

/*
 * Brief : Load the fonts
 */
void GameState::LoadFonts()
{
	_data->m_assetManager.LoadFont("Robotto Font", FONT); 
}

/*
 * Brief : Set all of the texts
 */
void GameState::SetTexts()
{
	_checkBoxDiagText = sf::Text("Diagonal Movement", _data->m_assetManager.GetFont("Robotto Font"), 20);
	_checkBoxDebugText = sf::Text("Debug mode", _data->m_assetManager.GetFont("Robotto Font"), 20);
}

/*
 * Brief : Set all of the textures
 */
void GameState::SetTextures()
{
	_background.setTexture(_data->m_assetManager.GetTexture("Game Background"));
	_pauseButton.setTexture(_data->m_assetManager.GetTexture("Pause Button"));
	_playButton.setTexture(_data->m_assetManager.GetTexture("Play Button"));
	_gridSprite.setTexture(_data->m_assetManager.GetTexture("Path"));
	_checkBoxDiagMode.setTexture(_data->m_assetManager.GetTexture("Check Box Unchecked"));
	_backwardDebug.setTexture(_data->m_assetManager.GetTexture("Backward Arrow"));
	_forwardDebug.setTexture(_data->m_assetManager.GetTexture("Forward Arrow"));
	_checkBoxDebugMode.setTexture(_data->m_assetManager.GetTexture("Check Box Unchecked"));
	_clearButton.setTexture(_data->m_assetManager.GetTexture("Clear Button"));
	_clearPathButton.setTexture(_data->m_assetManager.GetTexture("Clear Path Button"));
}

/*
 * Brief : Initialize the grid tiles with the empty texture
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

/*
 * Brief : Place an item on the grid
 *
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

/*
 * Brief : Reset an item on the grid
 *
 * @param : column : Column of the grid
 * @param : row : Row of the grid
 * @param : resetType : Type of the item that was previously placed
 * @param : itemContainer : Container of the item to update if needed
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

	if (GetGame()->_path.size() > 0)
	{
		ClearPath(); 
	}
}

/*
 * Brief : Draw the current step of the path
 *
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

/*
 * Brief : Clear the path with the empty texture & reset the grid array value
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

// TODO : Refactor this function
void GameState::PlacePiece(const GridPieces Piece)
{
	const sf::Vector2i touchPoint = _data->m_inputManager.GetMousePosition(_data->m_window);

	const sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
	const auto gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

	const auto gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

	int column, row;

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