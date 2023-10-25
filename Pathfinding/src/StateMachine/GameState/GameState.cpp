#include "GameState.h"
#include "../defined.h"
#include "../PauseState/PauseState.h"
#include "Game.h"

#include <sstream>
#include <iostream>

GameState::GameState(GameDataRef data) 
	: _data(data)
	, StartPlaced(false)
	, EndPlaced(false)
	, UseDiagonal(false)
	, DebugMode(false)
	, CurrentDebugStep(0)
	, _gridArray{ }
{
	startingPoint.x = -1;
	startingPoint.y = -1;
	endingPoint.x = -1;
	endingPoint.y = -1;
}

void GameState::Init()
{
	this->_data->m_assetManager.LoadTexture("Pause Button", PAUSE_BUTTON);
	this->_data->m_assetManager.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	this->_data->m_assetManager.LoadTexture("Grid Sprite", EMPTY_TILE);
	this->_data->m_assetManager.LoadTexture("Wall", WALL);
	this->_data->m_assetManager.LoadTexture("Path", PATH);
	this->_data->m_assetManager.LoadTexture("Start Point", START_POINT);
	this->_data->m_assetManager.LoadTexture("End Point", END_POINT);
	this->_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	this->_data->m_assetManager.LoadTexture("Check Box Checked", CHECK_BOX_CHECKED);
	this->_data->m_assetManager.LoadTexture("Check Box Unchecked", CHECK_BOX_UNCHECKED);
	this->_data->m_assetManager.LoadTexture("CheckPoint", CHECKPOINT);
	this->_data->m_assetManager.LoadTexture("Portal", PORTAL);
	this->_data->m_assetManager.LoadTexture("Forward Arrow", FORWARD_ARROW); 
	this->_data->m_assetManager.LoadTexture("Backward Arrow", BACKWARD_ARROW);
	
	this->_data->m_assetManager.LoadFont("Robotto Font", FONT); 
	
	_background.setTexture(this->_data->m_assetManager.GetTexture("Game Background"));
	this->_background.setScale(SCREEN_WIDTH / this->_background.getLocalBounds().width, SCREEN_HEIGHT / this->_background.getLocalBounds().height);
	
	_pauseButton.setScale(0.3f, 0.3f);
	_pauseButton.setTexture(this->_data->m_assetManager.GetTexture("Pause Button"));
	_pauseButton.setPosition((SCREEN_WIDTH - _pauseButton.getGlobalBounds().width), _pauseButton.getPosition().y);

	_playButton.setScale(0.3f, 0.3f);
	_playButton.setTexture(this->_data->m_assetManager.GetTexture("Play Button"));
	_playButton.setPosition(_playButton.getGlobalBounds().width, _playButton.getPosition().y);

	_gridSprite.setTexture(this->_data->m_assetManager.GetTexture("Path"));
	_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

	_checkBoxDiagMode.setScale(0.1f, 0.1f);
	_checkBoxDiagMode.setTexture(this->_data->m_assetManager.GetTexture("Check Box Unchecked"));
	_checkBoxDiagMode.setPosition((SCREEN_WIDTH / 4) - _checkBoxDiagMode.getGlobalBounds().width, (SCREEN_HEIGHT / 2) - _checkBoxDiagMode.getGlobalBounds().height );

	_checkBoxDiagText = sf::Text("Diagonal Movement", this->_data->m_assetManager.GetFont("Robotto Font"), 20);
	_checkBoxDiagText.setPosition((SCREEN_WIDTH / 4) - _checkBoxDiagText.getGlobalBounds().width - _checkBoxDiagMode.getGlobalBounds().width * 2, (SCREEN_HEIGHT / 2) - _checkBoxDiagMode.getGlobalBounds().height);

	_checkBoxDebugMode.setScale(0.1f, 0.1f);
	_checkBoxDebugMode.setTexture(this->_data->m_assetManager.GetTexture("Check Box Unchecked"));
	_checkBoxDebugMode.setPosition((SCREEN_WIDTH / 4) - _checkBoxDebugMode.getGlobalBounds().width, (SCREEN_HEIGHT / 2) - _checkBoxDebugMode.getGlobalBounds().height - _checkBoxDiagMode.getGlobalBounds().height);

	_checkBoxDebugText = sf::Text("Debug mode", this->_data->m_assetManager.GetFont("Robotto Font"), 20);
	_checkBoxDebugText.setPosition((SCREEN_WIDTH / 4) - _checkBoxDebugText.getGlobalBounds().width - _checkBoxDebugMode.getGlobalBounds().width * 2, (SCREEN_HEIGHT / 2) - _checkBoxDebugMode.getGlobalBounds().height - _checkBoxDiagMode.getGlobalBounds().height);

	_backwardDebug.setScale(0.5f, 0.5f);
	_backwardDebug.setTexture(this->_data->m_assetManager.GetTexture("Backward Arrow"));
	_backwardDebug.setPosition((SCREEN_WIDTH / 2) - _backwardDebug.getGlobalBounds().width/2, SCREEN_HEIGHT - _backwardDebug.getGlobalBounds().height );

	_forwardDebug.setScale(0.5f, 0.5f);
	_forwardDebug.setTexture(this->_data->m_assetManager.GetTexture("Forward Arrow"));
	_forwardDebug.setPosition((SCREEN_WIDTH / 2) + _forwardDebug.getGlobalBounds().width /2  , SCREEN_HEIGHT - _forwardDebug.getGlobalBounds().height);

	InitGridTiles();
}

void GameState::HandleInput()
{
	sf::Event event;

	while (this->_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->m_window.close();
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code &&this->_data->m_inputManager.IsMouseOverSprite( this->_pauseButton, this->_data->m_window))
		{
			this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->_data->m_inputManager.IsMouseOverSprite(this->_gridSprite, this->_data->m_window))
		{
			PlacePiece(START_PIECE);
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Right == event.key.code && this->_data->m_inputManager.IsMouseOverSprite(this->_gridSprite, this->_data->m_window))
		{
			PlacePiece(END_PIECE);
		}

		if (sf::Event::KeyReleased == event.type && sf::Keyboard::W == event.key.code)
		{
			if (this->_data->m_inputManager.IsMouseOverSprite(this->_gridSprite, this->_data->m_window))
			{
				PlacePiece(WALL_PIECE);
			}
		}
		
		if (sf::Event::KeyReleased == event.type && sf::Keyboard::C == event.key.code)
		{
			if (this->_data->m_inputManager.IsMouseOverSprite(this->_gridSprite, this->_data->m_window))
			{
				PlacePiece(CHECKPOINT_PIECE);
			}
		}

		if (sf::Event::KeyReleased == event.type && sf::Keyboard::P == event.key.code)
		{
			if (this->_data->m_inputManager.IsMouseOverSprite(this->_gridSprite, this->_data->m_window))
			{
				PlacePiece(PORTAL_PIECE);
			}
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->_data->m_inputManager.IsMouseOverSprite(this->_playButton, this->_data->m_window))
		{
			Play();
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_checkBoxDiagMode, sf::Mouse::Left, this->_data->m_window))
		{
			UseDiagonal = !UseDiagonal;
			_checkBoxDiagMode.setTexture(this->_data->m_assetManager.GetTexture(UseDiagonal ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_checkBoxDebugMode, sf::Mouse::Left, this->_data->m_window))
		{
			DebugMode = !DebugMode;
			_checkBoxDebugMode.setTexture(this->_data->m_assetManager.GetTexture(DebugMode ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->_data->m_inputManager.IsMouseOverSprite(this->_forwardDebug, this->_data->m_window))
		{
			if (DebugMode)
			{
				ForwardDebug();
			}
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->_data->m_inputManager.IsMouseOverSprite(this->_backwardDebug, this->_data->m_window))
		{
			if (DebugMode)
			{
				BackwardDebug();
			}
		}
	}
}

void GameState::Update(float dt)
{
}

void GameState::Draw(float dt)
{
	_data->m_window.clear();
	_data->m_window.draw(_background);
	_data->m_window.draw(_gridSprite);
	_data->m_window.draw(_playButton);
	_data->m_window.draw(_checkBoxDiagText);

	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; y++)
		{
			this->_data->m_window.draw(_gridPieces[x][y]);
		}
	}
	
	_data->m_window.draw(_forwardDebug);
	_data->m_window.draw(_backwardDebug);
	_data->m_window.draw(_checkBoxDebugText);
	_data->m_window.draw(_checkBoxDebugMode);
	_data->m_window.draw(_pauseButton);
	_data->m_window.draw(_checkBoxDiagMode);
	_data->m_window.display();
}

void GameState::InitGridTiles()
{
	sf::Vector2u tempSpriteSize = this->_data->m_assetManager.GetTexture("Grid Sprite").getSize();

	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; ++y)
		{
			float factor = static_cast<float>(1.f) / NB_COLUMNS;

			_gridPieces[x][y].setScale(factor, factor);
			_gridPieces[x][y].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));

			float positionX = _gridSprite.getPosition().x + ( x * _gridPieces[x][y].getGlobalBounds().width ) + x;
			float positionY = _gridSprite.getPosition().y + ( y * _gridPieces[x][y].getGlobalBounds().height)+ y;

			_gridPieces[x][y].setPosition(positionX,positionY);

			_gridArray[x][y] = EMPTY_PIECE;
		}
	}
}

void GameState::PlacePiece(GridPieces clickSide)
{
	sf::Vector2i touchPoint = this->_data->m_inputManager.GetMousePosition(this->_data->m_window);

	sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
	sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

	sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

	sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / NB_COLUMNS, gridSize.height / NB_LINES);

	int column, row;
	
	float columnWidth = _gridSprite.getGlobalBounds().width / NB_COLUMNS; 
	float rowHeight = _gridSprite.getGlobalBounds().height / NB_LINES; 

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

	switch (clickSide) {
	case START_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point")) {
			ResetStartPoint(column, row);
			break;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point") && !StartPlaced) {
			ResetEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall") && !StartPlaced) {
			ResetWall(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Portal")) {
			ResetPortal(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetCheckPoint(column, row);
		}

		if (!StartPlaced)
		{
			PlaceStartPoint(column, row);
		}

		break;

	case END_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point")) {
			ResetEndPoint(column, row);
			break;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point") && !EndPlaced) {
			ResetStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall") && !EndPlaced) {
			ResetWall(column, row);

		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Portal")) {
			ResetPortal(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetCheckPoint(column, row);
		}

		if (!EndPlaced)
		{
			PlaceEndPoint(column, row);
		}

		break;

	case WALL_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point")) {
			ResetEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point")) {
			ResetStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall")) {
			ResetWall(column, row);
			break;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Portal")) {
			ResetPortal(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetCheckPoint(column, row);
		}

		PlaceWall(column, row);
		
		break;

	case CHECKPOINT_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetCheckPoint(column, row);
			break;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point")) {
			ResetStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point")) {
			ResetEndPoint(column, row);		
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall")) {
			ResetWall(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Portal")) {
			ResetPortal(column, row);
		}
		
		PlaceCheckPoint(column, row); 
		break;

	case PORTAL_PIECE:
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Portal")) {
			ResetPortal(column, row);
			break;
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point")) {
			ResetStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point")) {
			ResetEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall")) {
			ResetWall(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetCheckPoint(column, row);
		}

		PlacePortal(column, row);
		break;

	default:
		break;
	}

}

void GameState::Play()
{
	CurrentDebugStep = -1;
	_path.clear();
	std::vector<sf::Vector2i> tempCheckPoints = CheckPoints;
	sf::Vector2i currentPoint = startingPoint;

	ClearPath();

	if (CheckMapValidity())
	{
		for (int i = 0; i < CheckPoints.size(); i++)
		{
			SortCheckpointsByDistance(tempCheckPoints, currentPoint);
			currentPoint = ProcessNextCheckpoint(tempCheckPoints, currentPoint);

			if (currentPoint.x == -1 || currentPoint.y == -1) // No path found to next checkpoint
			{
				return;
			}
		}		

		ProcessFinalPath(currentPoint);
	}
}

void GameState::SortCheckpointsByDistance(std::vector<sf::Vector2i>& checkpoints, const sf::Vector2i& fromPoint)
{
	std::sort(checkpoints.begin(), checkpoints.end(), [this, fromPoint](const sf::Vector2i& a, const sf::Vector2i& b) {
		float distA = CalculateDistance(fromPoint, a);
		float distB = CalculateDistance(fromPoint, b);
		return distA < distB;
		});
}

sf::Vector2i GameState::ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, sf::Vector2i& currentPoint)
{
	sf::Vector2i closestCheckpoint = checkpoints[0];

	int pathLength = _path.size();
	std::vector<Pair> tempPath;

	GetGame()->AStarAlgorithm(_gridArray, currentPoint, closestCheckpoint, UseDiagonal, tempPath);

	if (pathLength == tempPath.size())
	{
		return sf::Vector2i(-1, -1);
	}

	CheckPortalPath(currentPoint,closestCheckpoint,tempPath);

	if (!DebugMode)
	{
		for (int i = 0; i < _path.size(); i++)
		{
			DrawStepPath(_path.at(i),true);
		}
	}

	checkpoints.erase(checkpoints.begin());

	return closestCheckpoint;
}

void GameState::ProcessFinalPath(sf::Vector2i& currentPoint)
{
	std::vector<Pair> tempPath;

	GetGame()->AStarAlgorithm(_gridArray, currentPoint, endingPoint, UseDiagonal, tempPath);

	CheckPortalPath(currentPoint, endingPoint,tempPath);

	if (!DebugMode)
	{
		for (int i = 0; i < _path.size(); i++)
		{
			DrawStepPath(_path.at(i),true);
		}
	}
}

float GameState::CalculateDistance(const sf::Vector2i& point1, const sf::Vector2i& point2)
{
	float dx = static_cast<float>(point2.x - point1.x);
	float dy = static_cast<float>(point2.y - point1.y);
	return sqrt(dx * dx + dy * dy);
}

bool GameState::CheckMapValidity()
{
	return startingPoint.x != -1 && startingPoint.y != -1 && endingPoint.x != -1 && endingPoint.y != -1;
}

void GameState::ResetStartPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	StartPlaced = false;
	startingPoint = sf::Vector2i(-1, -1);
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
	ClearPath();
}

void GameState::ResetEndPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	EndPlaced = false;
	endingPoint = sf::Vector2i(-1, -1);
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
	ClearPath();
}

void GameState::ResetWall(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
	ClearPath();
}

void GameState::ResetCheckPoint(int column, int row)
{
	ClearPath();
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
	
	for (int i = 0; i < CheckPoints.size(); i++)
	{
		if (CheckPoints[i].x == column - 1 && CheckPoints[i].y == row - 1)
		{
			CheckPoints.erase(CheckPoints.begin() + i);
			break;
		}
	}
}

void GameState::ResetPortal(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
	ClearPath();

	for (int i = 0; i < Portals.size(); i++)
	{
		if (Portals[i].x == column - 1 && Portals[i].y == row - 1)
		{
			Portals.erase(Portals.begin() + i);
			break;
		}
	}
}

void GameState::PlaceStartPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Start Point"));
	StartPlaced = true;
	startingPoint = sf::Vector2i(column - 1, row - 1);
	_gridArray[column - 1][row - 1] = START_PIECE;
	ClearPath();
}

void GameState::PlaceEndPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("End Point"));
	EndPlaced = true;
	endingPoint = sf::Vector2i(column - 1, row - 1);
	_gridArray[column - 1][row - 1] = END_PIECE;
	ClearPath();
}

void GameState::PlaceWall(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Wall"));
	_gridArray[column - 1][row - 1] = WALL_PIECE;
	ClearPath();
}

void GameState::PlaceCheckPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("CheckPoint"));
	_gridArray[column - 1][row - 1] = CHECKPOINT_PIECE;
	CheckPoints.push_back(sf::Vector2i(column - 1, row - 1));
	ClearPath();
}

void GameState::PlacePortal(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Portal"));
	_gridArray[column - 1][row - 1] = PORTAL_PIECE;
	Portals.push_back(sf::Vector2i(column - 1, row - 1));
	ClearPath();
}

void GameState::CheckPortalPath(sf::Vector2i& currentPoint, sf::Vector2i& nextPoint, std::vector<Pair> basePath)
{
	if (Portals.size() > 0)
	{
		std::vector<Pair> tempPath;
		GetGame()->AStarAlgorithm(_gridArray, currentPoint, GetClosestPortal(currentPoint), UseDiagonal, tempPath);
		GetGame()->AStarAlgorithm(_gridArray, nextPoint, GetClosestPortal(nextPoint),UseDiagonal, tempPath);

		if (tempPath.size() < basePath.size())
		{
			for (int i = 0; i < tempPath.size(); i++)
			{
				_path.push_back(tempPath[i]);			
			}
			return;
		}
	}

	for (int i = 0; i < basePath.size(); i++)
	{
		_path.push_back(basePath[i]);
	}
}

sf::Vector2i& GameState::GetClosestPortal(sf::Vector2i& point)
{
	float minDistance = 99999;
	int minIndex = -1;
	
	for (int i = 0; i < Portals.size(); i++)
	{
		float distance = CalculateDistance(point, Portals[i]);

		if (distance < minDistance)
		{
			minDistance = distance;
			minIndex = i;
		}
	}

	return Portals[minIndex];
}

void GameState::ClearPath()
{
	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; y++)
		{
			if (_gridArray[x][y] == PATH_PIECE)
			{
				_gridArray[x][y] = EMPTY_PIECE;
				_gridPieces[x][y].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
			}
		}
	}
	_path.clear();
}

void GameState::ForwardDebug()
{
	if (_path.empty() || CurrentDebugStep + 1 >= _path.size() )
	{ 
		return;
	}

	CurrentDebugStep++;
	DrawStepPath(_path.at(CurrentDebugStep),true);
}

void GameState::BackwardDebug()
{
	if (_path.empty() || CurrentDebugStep < 0 )
	{
		return;
	}

	DrawStepPath(_path.at(CurrentDebugStep), false);
	CurrentDebugStep--;
}

void GameState::DrawStepPath(Pair step,bool isPath)
{
	_gridPieces[step.first][step.second].setTexture(this->_data->m_assetManager.GetTexture(isPath ? "Path" : "Grid Sprite"));
	_gridArray[step.first][step.second] = PATH_PIECE;
}
