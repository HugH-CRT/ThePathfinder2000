#include "GameState.h"
#include "../defined.h"
#include "../PauseState/PauseState.h"
#include "Game.h"

#include <sstream>
#include <iostream>

GameState::GameState(GameDataRef data) 
	: _data(data)
{
	
}

void GameState::Init()
{
	LoadTextures();
	SetTextures();
	
	_data->m_assetManager.LoadFont("Robotto Font", FONT); 
	
	m_background.setScale(SCREEN_WIDTH / m_background.getLocalBounds().width, SCREEN_HEIGHT / m_background.getLocalBounds().height);
	m_pauseButton.setScale(0.3f, 0.3f);
	m_playButton.setScale(0.3f, 0.3f);
	m_checkBoxDiagMode.setScale(0.1f, 0.1f);
	m_checkBoxDebugMode.setScale(0.1f, 0.1f);
	m_backwardDebug.setScale(0.5f, 0.5f);
	m_forwardDebug.setScale(0.5f, 0.5f);

	m_checkBoxDiagText = sf::Text("Diagonal Movement", _data->m_assetManager.GetFont("Robotto Font"), 20);
	m_checkBoxDebugText = sf::Text("Debug mode", _data->m_assetManager.GetFont("Robotto Font"), 20);
	
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
	sf::Event event{};

	while (_data->m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->m_window.close();
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code &&_data->m_inputManager.IsMouseOverSprite( m_pauseButton, _data->m_window))
		{
			_data->machine.AddState(StateRef(new PauseState(_data)), false);
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(m_gridSprite, _data->m_window))
		{
			PlacePiece(START_PIECE);
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Right == event.key.code && _data->m_inputManager.IsMouseOverSprite(m_gridSprite, _data->m_window))
		{
			PlacePiece(END_PIECE);
		}

		if (sf::Event::KeyReleased == event.type && sf::Keyboard::W == event.key.code)
		{
			if (_data->m_inputManager.IsMouseOverSprite(m_gridSprite, _data->m_window))
			{
				PlacePiece(WALL_PIECE);
			}
		}
		
		if (sf::Event::KeyReleased == event.type && sf::Keyboard::C == event.key.code)
		{
			if (_data->m_inputManager.IsMouseOverSprite(this->m_gridSprite, _data->m_window))
			{
				PlacePiece(CHECKPOINT_PIECE);
			}
		}

		if (sf::Event::KeyReleased == event.type && sf::Keyboard::P == event.key.code)
		{
			if (_data->m_inputManager.IsMouseOverSprite(m_gridSprite, _data->m_window))
			{
				PlacePiece(PORTAL_PIECE);
			}
		}

		if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(m_playButton, _data->m_window))
		{
			GetGame()->Play();
		}

		if (_data->m_inputManager.IsSpriteClicked(m_checkBoxDiagMode, sf::Mouse::Left, _data->m_window))
		{
			GetGame()->SetUseDiagonal(!GetGame()->IsUseDiagonal());
			m_checkBoxDiagMode.setTexture(_data->m_assetManager.GetTexture(GetGame()->IsUseDiagonal() ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (_data->m_inputManager.IsSpriteClicked(m_checkBoxDebugMode, sf::Mouse::Left, _data->m_window))
		{
			GetGame()->SetDebugMode(!GetGame()->IsDebugMode());
			m_checkBoxDebugMode.setTexture(_data->m_assetManager.GetTexture(GetGame()->IsDebugMode() ? "Check Box Checked" : "Check Box Unchecked"));
		}

		if (GetGame()->IsDebugMode())
		{
			if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(m_forwardDebug, _data->m_window))
			{
				GetGame()->ForwardDebug();
			}

			if (sf::Event::MouseButtonReleased == event.type && sf::Mouse::Left == event.key.code && _data->m_inputManager.IsMouseOverSprite(m_backwardDebug, _data->m_window))
			{
				GetGame()->BackwardDebug();
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
	_data->m_window.draw(m_background);
	_data->m_window.draw(m_gridSprite);
	_data->m_window.draw(m_playButton);
	_data->m_window.draw(m_checkBoxDiagText);

	for (const auto& m_gridPiece : m_gridPieces)
	{
		for (const auto& y : m_gridPiece)
		{
			_data->m_window.draw(y);
		}
	}
	
	_data->m_window.draw(m_forwardDebug);
	_data->m_window.draw(m_backwardDebug);
	_data->m_window.draw(m_checkBoxDebugText);
	_data->m_window.draw(m_checkBoxDebugMode);
	_data->m_window.draw(m_pauseButton);
	_data->m_window.draw(m_checkBoxDiagMode);
	_data->m_window.display();
}

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
}

void GameState::SetTextures()
{
	m_background.setTexture(_data->m_assetManager.GetTexture("Game Background"));
	m_pauseButton.setTexture(_data->m_assetManager.GetTexture("Pause Button"));
	m_playButton.setTexture(_data->m_assetManager.GetTexture("Play Button"));
	m_gridSprite.setTexture(_data->m_assetManager.GetTexture("Path"));
	m_checkBoxDiagMode.setTexture(_data->m_assetManager.GetTexture("Check Box Unchecked"));
	m_backwardDebug.setTexture(_data->m_assetManager.GetTexture("Backward Arrow"));
	m_forwardDebug.setTexture(_data->m_assetManager.GetTexture("Forward Arrow"));
	m_checkBoxDebugMode.setTexture(_data->m_assetManager.GetTexture("Check Box Unchecked"));
}

void GameState::InitGridTiles()
{
	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; ++y)
		{
			const float factor = 1.f / NB_COLUMNS;

			m_gridPieces[x][y].setScale(factor, factor);
			m_gridPieces[x][y].setTexture(_data->m_assetManager.GetTexture("Grid Sprite"));

			const float positionX = m_gridSprite.getPosition().x + ( x * m_gridPieces[x][y].getGlobalBounds().width ) + x;
			const float positionY = m_gridSprite.getPosition().y + ( y * m_gridPieces[x][y].getGlobalBounds().height)+ y;

			m_gridPieces[x][y].setPosition(positionX,positionY);
			
			GetGame()->SetGridArrayItem(x, y, EMPTY_PIECE); 
		}
	}
}

void GameState::PlaceItem(const int column, const int row, const std::string& textureName, GridPieces itemType, std::vector<sf::Vector2i>* itemContainer = nullptr)
{
	m_gridPieces[column - 1][row - 1].setTexture(_data->m_assetManager.GetTexture(textureName));
	GetGame()->GetGridArray()[column - 1][row - 1] = itemType;

	if (itemContainer) {
		itemContainer->push_back(sf::Vector2i(column - 1, row - 1));
	}

	sf::Vector2i point(column - 1, row - 1);
	
	if (itemType == START_PIECE) {
		GetGame()->SetStartingPoint(point);
	}
	else if (itemType == END_PIECE) {
		GetGame()->SetEndingPoint(point);
	}

	ClearPath();
}

void GameState::ResetItem(const int column, const int row, const std::string& resetTexture, GridPieces resetType, std::vector<sf::Vector2i>* itemContainer)
{
	m_gridPieces[column - 1][row - 1].setTexture(_data->m_assetManager.GetTexture(resetTexture));
	GetGame()->GetGridArray()[column - 1][row - 1] = EMPTY_PIECE;

	if (itemContainer) {
		for (int i = 0; i < itemContainer->size(); i++) {
			if (itemContainer->at(i).x == column - 1 && itemContainer->at(i).y == row - 1) {
				itemContainer->erase(itemContainer->begin() + i);
				break;
			}
		}
	}

	sf::Vector2i point(- 1, - 1);

	if (resetType == START_PIECE) {
		GetGame()->SetStartingPoint(point);
	}
	else if (resetType == END_PIECE) {
		GetGame()->SetEndingPoint(point);
	}

	if (GetGame()->GetPathSize() > 0)
	{
		ClearPath(); 
		std::cout << " Clean " << std::endl;
	}
}

void GameState::DrawStepPath(const Pair step, const bool isPath)
{
	m_gridPieces[step.first][step.second].setTexture(_data->m_assetManager.GetTexture(isPath ? "Path" : "Grid Sprite"));
	GetGame()->GetGridArray()[step.first][step.second] = PATH_PIECE;
}

void GameState::ClearPath()
{
	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; y++)
		{
			if (GetGame()->GetGridArray()[x][y] == PATH_PIECE)
			{
				GetGame()->GetGridArray()[x][y] = EMPTY_PIECE;
				m_gridPieces[x][y].setTexture(_data->m_assetManager.GetTexture("Grid Sprite"));
			}
		}
	}
	GetGame()->ClearPath();
}

// TODO : Refactor this function
void GameState::PlacePiece(GridPieces clickSide)
{
	sf::Vector2i touchPoint = _data->m_inputManager.GetMousePosition(_data->m_window);

	sf::FloatRect gridSize = m_gridSprite.getGlobalBounds();
	sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

	sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

	sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / NB_COLUMNS, gridSize.height / NB_LINES);

	int column, row;

	const float columnWidth = m_gridSprite.getGlobalBounds().width / NB_COLUMNS;
	const float rowHeight = m_gridSprite.getGlobalBounds().height / NB_LINES; 

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

	const bool StartPlaced = GetGame()->GetStartingPoint().x != -1 && GetGame()->GetStartingPoint().y != -1;
	const bool EndPlaced = GetGame()->GetEndingPoint().x != -1 && GetGame()->GetEndingPoint().y != -1;

	sf::Vector2i point(column - 1, row - 1);

	switch (clickSide) {
	case START_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", START_PIECE, nullptr);
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point") && !StartPlaced) {
			ResetItem(column, row, "Grid Sprite", END_PIECE, nullptr);
			GetGame()->SetEndingPoint(point);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall") && !StartPlaced) {
			ResetItem(column, row, "Grid Sprite", WALL_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", PORTAL_PIECE, GetGame()->GetPortals());
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", CHECKPOINT_PIECE, GetGame()->GetCheckPoints());

		}

		if (!StartPlaced)
		{
			PlaceItem(column, row, "Start Point", START_PIECE,nullptr);
		}

		break;

	case END_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", END_PIECE, nullptr);
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point") && !EndPlaced) {
			ResetItem(column, row, "Grid Sprite", START_PIECE, nullptr);
			GetGame()->SetStartingPoint(point);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall") && !EndPlaced) {
			ResetItem(column, row, "Grid Sprite", WALL_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", PORTAL_PIECE, GetGame()->GetPortals());

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", CHECKPOINT_PIECE, GetGame()->GetCheckPoints());

		}

		if (!EndPlaced)
		{
			PlaceItem(column, row, "End Point", END_PIECE, nullptr);
		}

		break;

	case WALL_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", END_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", START_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, "Grid Sprite", WALL_PIECE, nullptr);
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", PORTAL_PIECE, GetGame()->GetPortals());

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", CHECKPOINT_PIECE, GetGame()->GetCheckPoints());

		}

		PlaceItem(column, row, "Wall", WALL_PIECE, nullptr);
		
		break;

	case CHECKPOINT_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", CHECKPOINT_PIECE, GetGame()->GetCheckPoints());

			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", START_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", END_PIECE, nullptr);

		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, "Grid Sprite", WALL_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", PORTAL_PIECE, GetGame()->GetPortals());

		}
		
		PlaceItem(column, row, "CheckPoint", CHECKPOINT_PIECE, GetGame()->GetCheckPoints());

		break;

	case PORTAL_PIECE:
		if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Portal")) {
			ResetItem(column, row, "Grid Sprite", PORTAL_PIECE, GetGame()->GetPortals());
			break;
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Start Point")) {
			ResetItem(column, row, "Grid Sprite", START_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("End Point")) {
			ResetItem(column, row, "Grid Sprite", END_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("Wall")) {
			ResetItem(column, row, "Grid Sprite", WALL_PIECE, nullptr);
		}
		else if (m_gridPieces[column - 1][row - 1].getTexture() == &_data->m_assetManager.GetTexture("CheckPoint")) {
			ResetItem(column, row, "Grid Sprite", CHECKPOINT_PIECE, GetGame()->GetCheckPoints());
		}

		PlaceItem(column, row, "Portal", PORTAL_PIECE, GetGame()->GetPortals());

		break;

	default:
		break;
	}

}