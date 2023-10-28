/**
* @file Game.h
 *
 * @brief Logic of the game
 *
 * @author yoan.laurain@ynov.com
 *
 */

#ifndef GAME_H
#define GAME_H

#include "StateMachine.h"
#include "AssetManager/AssetManager.h"
#include "InputManager/InputManager.h"
#include "defined.h"

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

enum GridPieces : int;
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
	explicit Game(int width = 1280, int height = 720, const std::string& title = "DefaultTitle");
	~Game();

	std::vector<Pair> AStarAlgorithm(sf::Vector2i startingPoint, sf::Vector2i endingPoint, bool UseDiagonal, std::vector<Pair>& _path);

	void Run();
	
private: 

	const float frameRate = 1.0f / 60.0f;
	sf::Clock m_clock;

	GameDataRef m_data = std::make_shared<GameData>();
	bool _DebugMode;

	int _gridArray[NB_LINES][NB_COLUMNS];

#pragma region AStartAlgorithm

	bool IsCellInBoundOfTheGrid(int row, int col);

	bool IsNotAWall(int row, int col);

	bool IsDestination(int row, int col, Pair dest);

	double CalculateHeuristicValue(int row, int col, Pair dest);

	std::vector<Pair> tracePath(cell cellDetails[][NB_COLUMNS], Pair dest, std::vector<Pair>& path);

#pragma endregion AStartAlgorithm
	
	sf::Vector2i ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, const sf::Vector2i& currentPoint);
	void ProcessFinalPath(const sf::Vector2i& currentPoint);
	bool CheckMapValidity();

	sf::Vector2i  CheckPortalPath(const sf::Vector2i& currentPoint, const sf::Vector2i& nextPoint, std::vector<Pair>& basePath);
	sf::Vector2i PathToClosestPortal(const sf::Vector2i& point,std::vector<Pair>& finalPath);
	sf::Vector2i PathToClosestCheckPoint(const sf::Vector2i& point,std::vector<sf::Vector2i>& checkpoints,std::vector<Pair>& finalPath);

	std::vector<Pair> aStarSearch(Pair startingPoint, Pair endingPoint,bool UseDiagonal, std::vector<Pair>& path);
	
	void InitGridArray();
	void DrawPath();
	sf::Vector2i GetClosestCheckPoint(const sf::Vector2i& point, std::vector<sf::Vector2i>& checkpoints);
	void RemoveCheckPoint(const sf::Vector2i& point, std::vector<sf::Vector2i>& checkpoints);

public : 
	void Play();
	void ForwardDebug();
	void BackwardDebug();
	void ClearPath();
	void ResetGame();
	
	bool _UseDiagonal;

	int _CurrentDebugStep;

	std::vector<sf::Vector2i>* _CheckPoints;
	std::vector<sf::Vector2i>* _Portals;

	sf::Vector2i _StartingPoint;
	sf::Vector2i _EndingPoint;

	std::vector<Pair> _path;
	
	bool IsDebugMode() const;

	int(&GetGridArray())[NB_LINES][NB_COLUMNS]{
		return _gridArray;
	}
	
	void SetDebugMode(bool debugMode);
	void SetGridArrayItem(int column, int row, GridPieces piece);
};

Game* GetGame();

#endif /* GAME_H */