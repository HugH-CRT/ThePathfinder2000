#include "GameState.h"
#include "../defined.h"
#include "../PauseState/PauseState.h"

#include <sstream>
#include <iostream>

GameState::GameState(GameDataRef data) 
	: _data(data)
	, StartPlaced(false)
	, EndPlaced(false)
	, _gridArray{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }
{
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
	
	_background.setTexture(this->_data->m_assetManager.GetTexture("Game Background"));
	this->_background.setScale(SCREEN_WIDTH / this->_background.getLocalBounds().width, SCREEN_HEIGHT / this->_background.getLocalBounds().height);

	_pauseButton.setScale(0.3f, 0.3f);
	_pauseButton.setTexture(this->_data->m_assetManager.GetTexture("Pause Button"));
	_pauseButton.setPosition((SCREEN_WIDTH - _pauseButton.getGlobalBounds().width), _pauseButton.getPosition().y);

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

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
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

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; ++y)
		{
			float factor = static_cast<float>(1.f) / 3.f;

			_gridPieces[x][y].setScale(factor, factor);
			_gridPieces[x][y].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));

			float positionX = _gridSprite.getPosition().x + ( x * _gridPieces[x][y].getGlobalBounds().width);
			float positionY = _gridSprite.getPosition().y + ( y * _gridPieces[x][y].getGlobalBounds().height);

			_gridPieces[x][y].setPosition(positionX,positionY);
		}
	}
}

void GameState::PlacePiece(sf::Mouse::Button clickSide)
{
	sf::Vector2i touchPoint = this->_data->m_inputManager.GetMousePosition(this->_data->m_window);

	sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
	sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

	sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

	sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

	int column, row;
	
	if (gridLocalTouchPos.x < _gridSprite.getGlobalBounds().width / 3)
	{
		column = 1;
	}
	else if (gridLocalTouchPos.x < _gridSprite.getGlobalBounds().width / 3 * 2)
	{
		column = 2;
	}
	else if (gridLocalTouchPos.x < _gridSprite.getGlobalBounds().width)
	{
		column = 3;
	}

	if (gridLocalTouchPos.y < gridSectionSize.y )
	{
		row = 1;
	}
	else if (gridLocalTouchPos.y < gridSectionSize.y * 2)
	{
		row = 2;
	}
	else if (gridLocalTouchPos.y < _gridSprite.getGlobalBounds().height)
	{
		row = 3;
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

		PlaceWall(column, row);
	}
	
}

void GameState::ResetStartPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	StartPlaced = false;
	startingPoint = sf::Vector2i(-1, -1);
}

void GameState::ResetEndPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
	EndPlaced = false;
	endingPoint = sf::Vector2i(-1, -1);
}

void GameState::ResetWall(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Grid Sprite"));
}

void GameState::PlaceStartPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Start Point"));
	StartPlaced = true;
	startingPoint = sf::Vector2i(column - 1, row - 1);
}

void GameState::PlaceEndPoint(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("End Point"));
	EndPlaced = true;
	endingPoint = sf::Vector2i(column - 1, row - 1);
}

void GameState::PlaceWall(int column, int row)
{
	_gridPieces[column - 1][row - 1].setTexture(this->_data->m_assetManager.GetTexture("Wall"));
}
