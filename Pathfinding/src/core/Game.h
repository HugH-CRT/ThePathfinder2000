#ifndef GAME_H
#define GAME_H

#include "StateMachine.h"
#include "AssetManager/AssetManager.h"
#include "InputManager/InputManager.h"
#include "defined.h"

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

struct GameData
{
	StateMachine machine;
	sf::RenderWindow m_window;
	AssetManager m_assetManager;
	InputManager m_inputManager;
};

typedef std::shared_ptr<GameData> GameDataRef;
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > pPair;

struct cell {
	int parent_i, parent_j;

	double f, g, h; // f = g + h
};

class Game
{
public: 
	explicit Game(int width = 1280, int height = 720, std::string title = "DefaultTitle");

	std::vector<Pair> AStarAlgorithm(int gridArray[NB_LINES][NB_COLUMNS], sf::Vector2i startingPoint, sf::Vector2i endingPoint, bool UseDiagonal, std::vector<Pair>& _path);

private: 

	const float frameRate = 1.0f / 60.0f;
	sf::Clock m_clock;

	GameDataRef m_data = std::make_shared<GameData>();

	void Run();	

	bool isValid(int row, int col);

	bool isNotAWall(int grid[][NB_COLUMNS], int row, int col);

	bool isDestination(int row, int col, Pair dest);

	double calculateHValue(int row, int col, Pair dest);

	std::vector<Pair> tracePath(cell cellDetails[][NB_COLUMNS], Pair dest,std::vector<Pair>& path);

	std::vector<Pair> aStarSearch(int grid[][NB_COLUMNS], Pair src, Pair dest, bool UseDiagonal,std::vector<Pair>& path);
};

Game* GetGame();

#endif /* GAME_H */