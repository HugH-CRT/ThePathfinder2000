#include "GameState.h"
#include "../defined.h"
#include "../PauseState/PauseState.h"
#include "Game.h"

#include <sstream>
#include <iostream>

GameState::GameState(GameDataRef data) 
	: m_data(data)
	, m_UseDiagonal(false)
	, m_DebugMode(false)
	, m_CurrentDebugStep(0)
	, m_CheckPoints(new std::vector<sf::Vector2i>)
	, m_Portals(new std::vector<sf::Vector2i>)
	, _gridArray{ }
{
	m_StartingPoint.x = -1;
	m_StartingPoint.y = -1;
	m_EndingPoint.x = -1;
	m_EndingPoint.y = -1;
}

GameState::~GameState()
{
	delete m_CheckPoints;
	delete m_Portals;
}

void GameState::Init()
{
	LoadTextures();
	SetTextures();
	
	this->m_data->m_assetManager.LoadFont("Robotto Font", FONT); 
	
	this->m_background.setScale(SCREEN_WIDTH / this->m_background.getLocalBounds().width, SCREEN_HEIGHT / this->m_background.getLocalBounds().height);
	
	m_pauseButton.setScale(0.3f, 0.3f);
	m_playButton.setScale(0.3f, 0.3f);
	m_checkBoxDiagMode.setScale(0.1f, 0.1f);
	m_checkBoxDebugMode.setScale(0.1f, 0.1f);
	m_backwardDebug.setScale(0.5f, 0.5f);
	m_forwardDebug.setScale(0.5f, 0.5f);

	m_checkBoxDiagText = sf::Text("Diagonal Movement", this->m_data->m_assetManager.GetFont("Robotto Font"), 20);
	m_checkBoxDebugText = sf::Text("Debug mode", this->m_data->m_assetManager.GetFont("Robotto Font"), 20);
	
	m_pauseButton.setPosition((SCREEN_WIDTH - m_pauseButton.getGlobalBounds().width), m_pauseButton.getPosition().y);
	m_playButton.setPosition(m_playButton.getGlobalBounds().width, m_playButton.getPosition().y);
	m_gridSprite.setPosition((SCREEN_WIDTH / 2) - (m_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (m_gridSprite.getGlobalBounds().height / 2));
	m_checkBoxDiagMode.setPosition((SCREEN_WIDTH / 4) - m_checkBoxDiagMode.getGlobalBounds().width, (SCREEN_HEIGHT / 2) - m_checkBoxDiagMode.getGlobalBounds().height );
	m_checkBoxDiagText.setPosition((SCREEN_WIDTH / 4) - m_checkBoxDiagText.getGlobalBounds().width - m_checkBoxDiagMode.getGlobalBounds().width * 2, (SCREEN_HEIGHT / 2) - m_checkBoxDiagMode.getGlobalBounds().height);
	m_checkBoxDebugMode.setPosition((SCREEN_WIDTH / 4) - m_checkBoxDebugMode.getGlobalBounds().width, (SCREEN_HEIGHT / 2) - m_checkBoxDebugMode.getGlobalBounds().height - m_checkBoxDiagMode.getGlobalBounds().height);
	m_checkBoxDebugText.setPosition((SCREEN_WIDTH / 4) - m_checkBoxDebugText.getGlobalBounds().width - m_checkBoxDebugMode.getGlobalBounds().width * 2, (SCREEN_HEIGHT / 2) - m_checkBoxDebugMode.getGlobalBounds().height - m_checkBoxDiagMode.getGlobalBounds().height);
	m_backwardDebug.setPosition((SCREEN_WIDTH / 2) - m_backwardDebug.getGlobalBounds().width/2, SCREEN_HEIGHT - m_backwardDebug.getGlobalBounds().height );
	m_forwardDebug.setPosition((SCREEN_WIDTH / 2) + m_forwardDebug.getGlobalBounds().width /2  , SCREEN_HEIGHT - m_forwardDebug.getGlobalBounds().height);

	InitGridTiles();
}

void GameState::HandleInput()
{
	sf::Event event;

	while (this->m_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->m_data->m_window.close();
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code &&this->m_data->m_inputManager.IsMouseOverSprite( this->m_pauseButton, this->m_data->m_window))
		{
			this->m_data->machine.AddState(StateRef(new PauseState(m_data)), false);
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->m_data->m_inputManager.IsMouseOverSprite(this->m_gridSprite, this->m_data->m_window))
		{
			PlacePiece(START_PIECE);
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Right == event.key.code && this->m_data->m_inputManager.IsMouseOverSprite(this->m_gridSprite, this->m_data->m_window))
		{
			PlacePiece(END_PIECE);
		}

		if (sf::Event::KeyReleased == event.type && sf::Keyboard::W == event.key.code)
		{
			if (this->m_data->m_inputManager.IsMouseOverSprite(this->m_gridSprite, this->m_data->m_window))
			{
				PlacePiece(WALL_PIECE);
			}
		}
		
		if (sf::Event::KeyReleased == event.type && sf::Keyboard::C == event.key.code)
		{
			if (this->m_data->m_inputManager.IsMouseOverSprite(this->m_gridSprite, this->m_data->m_window))
			{
				PlacePiece(CHECKPOINT_PIECE);
			}
		}

		if (sf::Event::KeyReleased == event.type && sf::Keyboard::P == event.key.code)
		{
			if (this->m_data->m_inputManager.IsMouseOverSprite(this->m_gridSprite, this->m_data->m_window))
			{
				PlacePiece(PORTAL_PIECE);
			}
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->m_data->m_inputManager.IsMouseOverSprite(this->m_playButton, this->m_data->m_window))
		{
			Play();
		}

		if (this->m_data->m_inputManager.IsSpriteClicked(this->m_checkBoxDiagMode, sf::Mouse::Left, this->m_data->m_window))
		{
			m_UseDiagonal = !m_UseDiagonal;
			m_checkBoxDiagMode.setTexture(this->m_data->m_assetManager.GetTexture(m_UseDiagonal ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (this->m_data->m_inputManager.IsSpriteClicked(this->m_checkBoxDebugMode, sf::Mouse::Left, this->m_data->m_window))
		{
			m_DebugMode = !m_DebugMode;
			m_checkBoxDebugMode.setTexture(this->m_data->m_assetManager.GetTexture(m_DebugMode ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->m_data->m_inputManager.IsMouseOverSprite(this->m_forwardDebug, this->m_data->m_window))
		{
			if (m_DebugMode)
			{
				ForwardDebug();
			}
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && this->m_data->m_inputManager.IsMouseOverSprite(this->m_backwardDebug, this->m_data->m_window))
		{
			if (m_DebugMode)
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
	m_data->m_window.clear();
	m_data->m_window.draw(m_background);
	m_data->m_window.draw(m_gridSprite);
	m_data->m_window.draw(m_playButton);
	m_data->m_window.draw(m_checkBoxDiagText);

	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; y++)
		{
			this->m_data->m_window.draw(m_gridPieces[x][y]);
		}
	}
	
	m_data->m_window.draw(m_forwardDebug);
	m_data->m_window.draw(m_backwardDebug);
	m_data->m_window.draw(m_checkBoxDebugText);
	m_data->m_window.draw(m_checkBoxDebugMode);
	m_data->m_window.draw(m_pauseButton);
	m_data->m_window.draw(m_checkBoxDiagMode);
	m_data->m_window.display();
}

void GameState::LoadTextures()
{
	this->m_data->m_assetManager.LoadTexture("Pause Button", PAUSE_BUTTON);
	this->m_data->m_assetManager.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	this->m_data->m_assetManager.LoadTexture("Grid Sprite", EMPTY_TILE);
	this->m_data->m_assetManager.LoadTexture("Wall", WALL);
	this->m_data->m_assetManager.LoadTexture("Path", PATH);
	this->m_data->m_assetManager.LoadTexture("Start Point", START_POINT);
	this->m_data->m_assetManager.LoadTexture("End Point", END_POINT);
	this->m_data->m_assetManager.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
	this->m_data->m_assetManager.LoadTexture("Check Box Checked", CHECK_BOX_CHECKED);
	this->m_data->m_assetManager.LoadTexture("Check Box Unchecked", CHECK_BOX_UNCHECKED);
	this->m_data->m_assetManager.LoadTexture("CheckPoint", CHECKPOINT);
	this->m_data->m_assetManager.LoadTexture("Portal", PORTAL);
	this->m_data->m_assetManager.LoadTexture("Forward Arrow", FORWARD_ARROW);
	this->m_data->m_assetManager.LoadTexture("Backward Arrow", BACKWARD_ARROW);
}

void GameState::SetTextures()
{
	m_background.setTexture(this->m_data->m_assetManager.GetTexture("Game Background"));
	m_pauseButton.setTexture(this->m_data->m_assetManager.GetTexture("Pause Button"));
	m_playButton.setTexture(this->m_data->m_assetManager.GetTexture("Play Button"));
	m_gridSprite.setTexture(this->m_data->m_assetManager.GetTexture("Path"));
	m_checkBoxDiagMode.setTexture(this->m_data->m_assetManager.GetTexture("Check Box Unchecked"));
	m_backwardDebug.setTexture(this->m_data->m_assetManager.GetTexture("Backward Arrow"));
	m_forwardDebug.setTexture(this->m_data->m_assetManager.GetTexture("Forward Arrow"));
	m_checkBoxDebugMode.setTexture(this->m_data->m_assetManager.GetTexture("Check Box Unchecked"));
}

void GameState::InitGridTiles()
{
	sf::Vector2u tempSpriteSize = this->m_data->m_assetManager.GetTexture("Grid Sprite").getSize();

	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; ++y)
		{
			float factor = static_cast<float>(1.f) / NB_COLUMNS;

			m_gridPieces[x][y].setScale(factor, factor);
			m_gridPieces[x][y].setTexture(this->m_data->m_assetManager.GetTexture("Grid Sprite"));

			float positionX = m_gridSprite.getPosition().x + ( x * m_gridPieces[x][y].getGlobalBounds().width ) + x;
			float positionY = m_gridSprite.getPosition().y + ( y * m_gridPieces[x][y].getGlobalBounds().height)+ y;

			m_gridPieces[x][y].setPosition(positionX,positionY);

			_gridArray[x][y] = EMPTY_PIECE;
		}
	}
}

void GameState::PlaceItem(int column, int row, const std::string& textureName, int itemType, std::vector<sf::Vector2i>* itemContainer = nullptr)
{
	m_gridPieces[column - 1][row - 1].setTexture(this->m_data->m_assetManager.GetTexture(textureName));
	_gridArray[column - 1][row - 1] = itemType;

	if (itemType == START_PIECE) {
		m_StartingPoint = sf::Vector2i(column - 1, row - 1);
	}
	else if (itemType == END_PIECE) {
		m_EndingPoint = sf::Vector2i(column - 1, row - 1);
	}

	if (itemContainer) {
		itemContainer->push_back(sf::Vector2i(column - 1, row - 1));
	}

	ClearPath();
}

void GameState::ResetItem(int column, int row, const std::string& resetTexture, int resetType, std::vector<sf::Vector2i>* itemContainer)
{
	m_gridPieces[column - 1][row - 1].setTexture(this->m_data->m_assetManager.GetTexture(resetTexture));
	_gridArray[column - 1][row - 1] = resetType;

	if (itemContainer) {
		for (int i = 0; i < itemContainer->size(); i++) {
			if (itemContainer->at(i).x == column - 1 && itemContainer->at(i).y == row - 1) {
				itemContainer->erase(itemContainer->begin() + i);
				break;
			}
		}
	}

	ClearPath(); // TODO : Ne pas clean à chaque fois mais uniquement si il faut
}

void GameState::DrawStepPath(Pair step, bool isPath)
{
	m_gridPieces[step.first][step.second].setTexture(this->m_data->m_assetManager.GetTexture(isPath ? "Path" : "Grid Sprite"));
	_gridArray[step.first][step.second] = PATH_PIECE;
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
				m_gridPieces[x][y].setTexture(this->m_data->m_assetManager.GetTexture("Grid Sprite"));
			}
		}
	}
	_path.clear();
}







void GameState::PlacePiece(GridPieces clickSide)
{
	sf::Vector2i touchPoint = this->m_data->m_inputManager.GetMousePosition(this->m_data->m_window);

	sf::FloatRect gridSize = m_gridSprite.getGlobalBounds();
	sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

	sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

	sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / NB_COLUMNS, gridSize.height / NB_LINES);

	int column, row;
	
	float columnWidth = m_gridSprite.getGlobalBounds().width / NB_COLUMNS; 
	float rowHeight = m_gridSprite.getGlobalBounds().height / NB_LINES; 

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

	bool StartPlaced = m_StartingPoint.x != -1 && m_StartingPoint.y != -1;
	bool EndPlaced = m_EndingPoint.x != -1 && m_EndingPoint.y != -1;

	switch (clickSide) {
	case START_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_StartingPoint = sf::Vector2i(-1, -1);
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("End Point") && !StartPlaced) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_EndingPoint = sf::Vector2i(-1, -1);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Wall") && !StartPlaced) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_Portals);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_CheckPoints);

		}

		if (!StartPlaced)
		{
			PlaceItem(column, row, "Start Point", START_PIECE,nullptr);
		}

		break;

	case END_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_EndingPoint = sf::Vector2i(-1, -1);

			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Start Point") && !EndPlaced) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_StartingPoint = sf::Vector2i(-1, -1);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Wall") && !EndPlaced) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_Portals);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_CheckPoints);

		}

		if (!EndPlaced)
		{
			PlaceItem(column, row, "End Point", END_PIECE, nullptr);
		}

		break;

	case WALL_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_EndingPoint = sf::Vector2i(-1, -1);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_StartingPoint = sf::Vector2i(-1, -1);;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_Portals);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_CheckPoints);

		}

		PlaceItem(column, row, "Wall", WALL_PIECE, nullptr);
		
		break;

	case CHECKPOINT_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_CheckPoints);

			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_StartingPoint = sf::Vector2i(-1, -1);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_EndingPoint = sf::Vector2i(-1, -1);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_Portals);

		}
		
		PlaceItem(column, row, "CheckPoint", CHECKPOINT_PIECE, m_CheckPoints);

		break;

	case PORTAL_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_Portals);
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_StartingPoint = sf::Vector2i(-1, -1);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
			m_EndingPoint = sf::Vector2i(-1, -1);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &this->m_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", EMPTY_PIECE, m_CheckPoints);

		}

		PlaceItem(column, row, "Portal", PORTAL_PIECE, m_Portals);

		break;

	default:
		break;
	}

}










void GameState::Play()
{
	m_CurrentDebugStep = -1;
	_path.clear();
	std::vector<sf::Vector2i> tempCheckPoints = *m_CheckPoints;
	sf::Vector2i currentPoint = m_StartingPoint;

	ClearPath();

	if (CheckMapValidity())
	{
		for (int i = 0; i < m_CheckPoints->size(); i++)
		{
			currentPoint = ProcessNextCheckpoint(tempCheckPoints, currentPoint);

			if (currentPoint.x == -1 || currentPoint.y == -1) // No path found to next checkpoint
			{
				return;
			}
		}		

		ProcessFinalPath(currentPoint);
	}

	//delete tempCheckPoints;
}

sf::Vector2i GameState::ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, sf::Vector2i& currentPoint)
{
	sf::Vector2i closestCheckpoint = checkpoints[0];

	int pathLength = _path.size();
	std::vector<Pair> tempPath;

	GetGame()->AStarAlgorithm(_gridArray, currentPoint, closestCheckpoint, m_UseDiagonal, tempPath);

	if (pathLength == tempPath.size())
	{
		return sf::Vector2i(-1, -1);
	}

	CheckPortalPath(currentPoint,closestCheckpoint,tempPath);

	if (!m_DebugMode)
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

	GetGame()->AStarAlgorithm(_gridArray, currentPoint, m_EndingPoint, m_UseDiagonal, tempPath);

	CheckPortalPath(currentPoint, m_EndingPoint,tempPath);

	if (!m_DebugMode)
	{
		for (int i = 0; i < _path.size(); i++)
		{
			DrawStepPath(_path.at(i),true);
		}
	}
}

bool GameState::CheckMapValidity()
{
	return m_StartingPoint.x != -1 && m_StartingPoint.y != -1 && m_EndingPoint.x != -1 && m_EndingPoint.y != -1;
}

void GameState::CheckPortalPath(sf::Vector2i& currentPoint, sf::Vector2i& nextPoint, std::vector<Pair> basePath)
{
	if (m_Portals->size() > 0)
	{
		std::vector<Pair> tempPath;
		GetGame()->AStarAlgorithm(_gridArray, currentPoint, GetClosestPortal(currentPoint), m_UseDiagonal, tempPath);
		GetGame()->AStarAlgorithm(_gridArray, nextPoint, GetClosestPortal(nextPoint),m_UseDiagonal, tempPath);

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
	
	for (int i = 0; i < m_Portals->size(); i++)
	{
		std::vector<Pair> tempPath;

		sf::Vector2i currentPoint = m_Portals->at(i);
		GetGame()->AStarAlgorithm(_gridArray, currentPoint, point, m_UseDiagonal, tempPath);

		if (tempPath.size() == 0)
		{
			continue;
		}

		if (tempPath.size() < minDistance)
		{
			minDistance = tempPath.size();
			minIndex = i;
		}
	}

	if (minIndex == -1)
	{
		return point;
	}

	return m_Portals->at(minIndex);
}

void GameState::ForwardDebug()
{
	if (_path.empty() || m_CurrentDebugStep + 1 >= _path.size() )
	{ 
		return;
	}

	m_CurrentDebugStep++;
	DrawStepPath(_path.at(m_CurrentDebugStep),true);
}

void GameState::BackwardDebug()
{
	if (_path.empty() || m_CurrentDebugStep < 0 )
	{
		return;
	}

	DrawStepPath(_path.at(m_CurrentDebugStep), false);
	m_CurrentDebugStep--;
}