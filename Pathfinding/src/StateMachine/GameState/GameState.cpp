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

		if (this->_data->m_inputManager.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->m_window))
		{
			this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->m_window))
		{
			PlacePiece(sf::Mouse::Left);
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_gridSprite, sf::Mouse::Right, this->_data->m_window))
		{
			PlacePiece(sf::Mouse::Right);
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_gridSprite, sf::Mouse::Middle, this->_data->m_window))
		{
			PlacePiece(sf::Mouse::Middle);
		}

		if (this->_data->m_inputManager.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->m_window))
		{
			Play();
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

	for (int x = 0; x < NB_LINES; x++)
	{
		for (int y = 0; y < NB_COLUMNS; y++)
		{
			this->_data->m_window.draw(_gridPieces[x][y]);
		}
	}
	
	_data->m_window.draw(_pauseButton);
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

void GameState::PlacePiece(sf::Mouse::Button clickSide)
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

	if (clickSide == sf::Mouse::Left)
	{
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Grid Sprite") && !StartPlaced)
		{
			PlaceStartPoint(column, row );
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point"))
		{
			PlaceStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point") && !StartPlaced)
		{
			ResetEndPoint(column, row );
			PlaceStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall") && !StartPlaced)
		{
			ResetWall(column, row);
			PlaceStartPoint(column, row);
		}
	}
	else if (clickSide == sf::Mouse::Right)
	{
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Grid Sprite") && !EndPlaced)
		{
			PlaceEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point"))
		{
			ResetEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point") && !EndPlaced)
		{
			ResetStartPoint(column, row);
			PlaceEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall") && !EndPlaced)
		{
			ResetWall(column, row);
			PlaceEndPoint(column, row);
		}
	}
	else if (clickSide == sf::Mouse::Middle)
	{
		if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("End Point"))
		{
			ResetEndPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Start Point"))
		{
			ResetStartPoint(column, row);
		}
		else if (_gridPieces[column - 1][row - 1].getTexture() == &this->_data->m_assetManager.GetTexture("Wall"))
		{
			ResetWall(column, row);
		}
		else
		{
			PlaceWall(column, row);
		}
	}
}

void GameState::Play()
{
	ClearPath();
	if (CheckMapValidity())
	{
		stack<Pair> path = GetGame()->AStarAlgorithm(_gridArray,startingPoint, endingPoint);

		while (!path.empty())
		{
			Pair p = path.top();
			path.pop();
			_gridPieces[p.first][p.second].setTexture(this->_data->m_assetManager.GetTexture("Path"));
			_gridArray[p.first][p.second] = PATH_PIECE;
		}
	}
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
}

void GameState::ResetEndPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	EndPlaced = false;
	endingPoint = sf::Vector2i(-1, -1);
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
}

void GameState::ResetWall(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	_gridArray[column - 1][row - 1] = EMPTY_PIECE;
}

void GameState::PlaceStartPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Start Point"));
	StartPlaced = true;
	startingPoint = sf::Vector2i(column - 1, row - 1);
	_gridArray[column - 1][row - 1] = START_PIECE;
}

void GameState::PlaceEndPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("End Point"));
	EndPlaced = true;
	endingPoint = sf::Vector2i(column - 1, row - 1);
	_gridArray[column - 1][row - 1] = END_PIECE;
}

void GameState::PlaceWall(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Wall"));
	_gridArray[column - 1][row - 1] = WALL_PIECE;
}

void GameState::DrawPath(stack<Pair> Path)
{
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
}
