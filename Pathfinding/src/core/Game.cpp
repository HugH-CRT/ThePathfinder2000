/**
* @file Game.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "Game.h"
#include "SplashState/SplashState.h"
#include "macro.h"
#include "logger.h"

#include <set>
#include <GameState/GameState.h>

using namespace std;

/**
* @fn Game
* @brief Default constructor
* @param width
* @param height
* @param title
*/
Game::Game(const int width, const int height, const std::string& title) :
    _UseDiagonal(false)
    , _DebugMode(false)
    , _CurrentDebugStep(0)
    , _gridArray{}
    , _CheckPoints(new std::vector<sf::Vector2i>)
    , _Portals(new std::vector<sf::Vector2i>)
{
    ResetGame();

    // Start the game with the splash screen
	m_data->m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	m_data->machine.AddState(std::make_unique<SplashState>(m_data));
}

/**
* @fn ~Game
* @brief 
*/
Game::~Game()
{
    DELETE_PTR(_CheckPoints)
    DELETE_PTR(_Portals)
}

#pragma region AStartAlgorithm

/**
* @fn AStarAlgorithm
* @brief  
* @param startingPoint
* @param endingPoint
* @param UseDiagonal
* @param _path
* @return 
*/
std::vector<Pair> Game::AStarAlgorithm(sf::Vector2i startingPoint, sf::Vector2i endingPoint, bool UseDiagonal,
    std::vector<Pair>& _path)
{
    const Pair start = std::make_pair(startingPoint.x, startingPoint.y);
    const Pair dest = std::make_pair(endingPoint.x, endingPoint.y);

    return aStarSearch(start, dest, UseDiagonal, _path);
}

/**
* @fn Run
* @brief
*/
void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = m_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (m_data->m_window.isOpen())
	{
		m_data->machine.ProcessStateChanges();
		newTime = m_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= frameRate)
		{
			m_data->machine.GetActiveState()->HandleInput();
			m_data->machine.GetActiveState()->Update(frameRate);	

			accumulator -= frameRate;
		}

		interpolation = accumulator / frameRate;
		m_data->machine.GetActiveState()->Draw(interpolation);
	}
}

/**
* @fn IsCellInBoundOfTheGrid
* @brief  
* @param row
* @param col
* @return 
*/
bool Game::IsCellInBoundOfTheGrid(const int row, const int col)
{
    return (row >= 0) && (row < NB_LINES) && (col >= 0)
        && (col < NB_COLUMNS);
}

/**
* @fn IsNotAWall
* @brief  
* @param row
* @param col
* @return 
*/
bool Game::IsNotAWall(const int row, const int col)
{
    return _gridArray[row][col] != WALL_PIECE;
}

/**
* @fn IsDestination
* @brief  
* @param row
* @param col
* @param dest
* @return 
*/
bool Game::IsDestination(const int row, const int col, const Pair dest)
{
    return row == dest.first && col == dest.second;
}

/**
* @fn CalculateHeuristicValue
* @brief  
* @param row
* @param col
* @param dest
* @return 
*/
double Game::CalculateHeuristicValue(const int row, const int col, const Pair dest)
{
    return sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second));
}

/**
* @fn tracePath
* @brief Fill the path vector with the path from the starting point to the ending point
* @param cellDetails
* @param dest
* @param path
*/
std::vector<Pair> Game::tracePath(cell cellDetails[][NB_COLUMNS], const Pair dest,std::vector<Pair>& path)
{
    int row = dest.first;
    int col = dest.second;
    
    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col)) {

		if (row != dest.first || col != dest.second) {
            path.emplace_back(row, col);
		}

        const int temp_row = cellDetails[row][col].parent_i;
        const int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;    
    }
    
    path.emplace_back(row, col);
    
	return path;
}

/**
* @fn aStarSearch
* @brief
* @param startingPoint
* @param endingPoint
* @param UseDiagonal
* @param path
*/
std::vector<Pair> Game::aStarSearch(const Pair startingPoint, const Pair endingPoint, const bool UseDiagonal,std::vector<Pair>& path)
{
    // If the start is out of range
    if (IsCellInBoundOfTheGrid(startingPoint.first, startingPoint.second) == false) {
        Logger::debug("Source is invalid \n");
        return path;
    }

    // If the destination is out of range
    if (IsCellInBoundOfTheGrid(endingPoint.first, endingPoint.second) == false) {
        Logger::debug("Destination is invalid \n");
        return path;
    }

    // Either the source or the destination is blocked
    if (IsNotAWall(startingPoint.first, startingPoint.second) == false
        || IsNotAWall( endingPoint.first, endingPoint.second)
        == false) {
        Logger::debug("Source or the destination is blocked \n");
        return path;
    }

    // If the destination cell is the same as source cell
    if (IsDestination(startingPoint.first, startingPoint.second,endingPoint)
        == true) {
        Logger::debug("We are already at the destination \n");
        return path;
    }

    bool closedList[NB_LINES][NB_COLUMNS];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[NB_LINES][NB_COLUMNS];

    int i, j;

    // Initialising the parameters of the cells to infinity
    for (i = 0; i < NB_LINES; i++) {
        for (j = 0; j < NB_COLUMNS; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = startingPoint.first, j = startingPoint.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;

    // Put the starting cell on the open list and set its 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool foundDest = false;

    // Available movements   
    std::vector dx = { -1, 1, 0, 0 };
    std::vector dy = { 0, 0, 1, -1 };

    if (UseDiagonal)
    {
        dx.push_back(-1);
        dx.push_back(1);
        dx.push_back(-1);
        dx.push_back(1);

        dy.push_back(-1);
        dy.push_back(1);
        dy.push_back(1);
        dy.push_back(-1);
    }

    while (!openList.empty()) {
        
        // Extraire le n�ud de la liste ouverte avec le co�t "f" le plus bas
        pPair p = *openList.begin();
        openList.erase(openList.begin());

        int i = p.second.first;
        int j = p.second.second;

        // V�rifier si c'est la destination
        if (IsDestination(i, j,endingPoint)) {
            Logger::debug("The destination cell is found\n");
            
            return tracePath(cellDetails,endingPoint,path);
        }

        // Marquer le n�ud actuel comme visit�
        closedList[i][j] = true;

        // Parcourir les voisins
        for (int k = 0; k < dx.size(); k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];

            if (IsCellInBoundOfTheGrid(ni, nj) && !closedList[ni][nj] && IsNotAWall(ni, nj)) {
                double gNew = cellDetails[i][j].g + ((k < 4) ? 1.0 : 1.414);
                double hNew = CalculateHeuristicValue(ni, nj,endingPoint);
                double fNew = gNew + hNew;

                if (cellDetails[ni][nj].f == FLT_MAX || cellDetails[ni][nj].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(ni, nj)));
                    cellDetails[ni][nj].f = fNew;
                    cellDetails[ni][nj].g = gNew;
                    cellDetails[ni][nj].h = hNew;
                    cellDetails[ni][nj].parent_i = i;
                    cellDetails[ni][nj].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found due to blockages)
    if (foundDest == false)
    {
        Logger::debug("Failed to find the Destination Cell\n");
    }

	return path;
}

#pragma endregion AStartAlgorithm

/**
* @fn Play
* @brief
*/
void Game::Play()
{
    _CurrentDebugStep = -1;
    std::vector<sf::Vector2i> tempCheckPoints = *_CheckPoints;
    sf::Vector2i currentPoint = _StartingPoint;

    ClearPath();

    if (CheckMapValidity()) // Check if the starting point and the ending point are set
    {
        bool AllCheckPointsReached = true;
        
        for (int i = 0; i < _CheckPoints->size(); i++) // Loop through all the checkpoints
        {
            currentPoint = ProcessNextCheckpoint(tempCheckPoints, currentPoint); // Get the next checkpoint and path to it
            
            if (currentPoint.x == -1 || currentPoint.y == -1) // No path found to next checkpoint
            {
                AllCheckPointsReached = false;
                _path.clear();
                return;
            }
        }

        if ( AllCheckPointsReached ) // Go to the ending point
        {
            ProcessFinalPath(currentPoint);
        }
    }
}

/**
* @fn ProcessNextCheckpoint
* @brief Process the next checkpoint, Draw the shortest path from the current point to the next checkpoint
*
* @param checkpoints : All remaining checkpoints to reach
* @param currentPoint : the current point we are at
*
* @return the next place to start from
*/
sf::Vector2i Game::ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, const sf::Vector2i& currentPoint)
{
    std::vector<Pair> tempPath; // hold the path to the next checkpoint
    
    sf::Vector2i closestCheckPoint = PathToClosestCheckPoint(currentPoint,checkpoints, tempPath);

    // At this point tempPath hold or not the path to the next checkpoint using the A* algorithm

    // We know check way trough portal and change the path if it is shorter
    CheckPortalPath(currentPoint, closestCheckPoint, tempPath); 

    if (!tempPath.empty()) // remove checkpoint if reached by any way
    {
        RemoveCheckPoint(closestCheckPoint, checkpoints);
        return closestCheckPoint;
    }
        
    return {-1,-1};
}

/**
* @fn ProcessFinalPath
* @brief Draw the final path from the current point to the ending point
* @param currentPoint : the current point
*/
void Game::ProcessFinalPath(const sf::Vector2i& currentPoint)
{
    std::vector<Pair> tempPath;

    GetGame()->AStarAlgorithm( _EndingPoint,currentPoint,_UseDiagonal, tempPath);

    sf::Vector2i closestPortal = CheckPortalPath(currentPoint, _EndingPoint, tempPath);

    if ( !tempPath.empty() || closestPortal.x != -1 && closestPortal.y != -1)
    {
        DrawPath();
    }
}

/**
* @fn CheckMapValidity
* @brief Verify if the starting point and the ending point are set
*/
bool Game::CheckMapValidity()
{
    return _StartingPoint.x != -1 && _StartingPoint.y != -1 && _EndingPoint.x != -1 && _EndingPoint.y != -1;
}

/**
* @fn CheckPortalPath
* @brief Check if the path through a portal is shorter than the base path
* @param currentPoint
* @param nextPoint
* @param basePath
*/
sf::Vector2i Game::CheckPortalPath(const sf::Vector2i& currentPoint, const sf::Vector2i& nextPoint, std::vector<Pair>& basePath)
{
    if (!_Portals->empty())
    {
        std::vector<Pair> tempPath; 

        const sf::Vector2i closestPortalStart = PathToClosestPortal(currentPoint,tempPath); 
        
        std::reverse(tempPath.begin(), tempPath.end());

        const sf::Vector2i closestPortalNextPoint = PathToClosestPortal(nextPoint,tempPath);

        const bool PointFound = closestPortalStart.x != -1 && closestPortalStart.y != -1 && closestPortalNextPoint.x != -1 && closestPortalNextPoint.y != -1; 
  
        if ( PointFound && (tempPath.size() < basePath.size() || basePath.empty() )  && !tempPath.empty())
        {
            for (auto i : tempPath)
            {
                _path.push_back(i);
                basePath.push_back(i);
            }
            
            if ( closestPortalNextPoint.x != -1 && closestPortalNextPoint.y != -1)
            {
                return closestPortalNextPoint;
            }
            return closestPortalStart;
        }
    }
    
    for (auto i : basePath)
    {
        _path.push_back(i);
    }
        
    return {-1, -1};
}

/**
* @fn PathToClosestPortal
* @brief Get the path to the closest portal from a point using the A* algorithm
*
* @param point : the point from which we want to find the closest portal
* @param finalPath : the path to the closest portal we are building
*
* @return the closest portal to the point
*/
sf::Vector2i Game::PathToClosestPortal(const sf::Vector2i& point,std::vector<Pair>& finalPath)
{
    float minDistance =  std::numeric_limits<float>::max();
    int minIndex = -1;

    std::vector<Pair> tempPath;
    
    for (int i = 0; i < _Portals->size(); i++)
    {
        std::vector<Pair> fPath;
        const sf::Vector2i currentPoint = _Portals->at(i);
        GetGame()->AStarAlgorithm( point, currentPoint, _UseDiagonal, fPath);

        // If the path is shorter than the current shortest path
        if (fPath.size() < minDistance && !fPath.empty())
        {
            minDistance = fPath.size();
            minIndex = i;
            fPath.pop_back();// remove portal as we want to tp not go over it
            tempPath = fPath;
        }
    }

    if ( minIndex != -1 ) // if a path was found
    {
        for (auto i : tempPath) // add the path to the final path
        {
            finalPath.push_back(i);
        }
        return _Portals->at(minIndex); // return the closest portal
    }
    return {-1, -1};
}

/**
* @fn PathToClosestCheckPoint
* @brief Get the path to the closest checkpoint from a point using the A* algorithm
*
* @param point : the point from which we want to find the closest checkpoint
* @param checkpoints : the checkpoints we want to check
* @param finalPath : the path to the closest checkpoint we are building
*
* @return the closest checkpoint to the point
*/
sf::Vector2i Game::PathToClosestCheckPoint(const sf::Vector2i& point, std::vector<sf::Vector2i>& checkpoints, std::vector<Pair>& finalPath)
{
    const sf::Vector2i closestCheckPoint = GetClosestCheckPoint(point,checkpoints);
    
    GetGame()->AStarAlgorithm(closestCheckPoint, point, _UseDiagonal, finalPath);

    if (!finalPath.empty()) // Path found ( portal not included )
    {
        finalPath.pop_back(); // remove checkpoint as we dont want to go over it
    }
    
    return closestCheckPoint;
}

/**
* @fn InitGridArray
* @brief Initialize the grid array with empty pieces
*/
void Game::InitGridArray()
{
    for (auto& i : _gridArray)
    {
        for (int& j : i)
        {
            j = EMPTY_PIECE;
        }
    }
}

/**
* @fn DrawPath
* @brief Draw the path on the grid
*/
void Game::DrawPath()
{
    if (!_DebugMode)
    {
        for (const auto& i : _path)
        {
            dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(i, true);
        }
    }
}

/**
* @fn RemoveCheckPoint
* @brief Remove a checkpoint from the checkpoints vector
* @param point
* @param checkpoints
*/
void Game::RemoveCheckPoint(const sf::Vector2i& point, std::vector<sf::Vector2i>& checkpoints)
{
    for ( auto it = checkpoints.begin(); it != checkpoints.end(); ++it )
    {
        if ( *it == point )
        {
            checkpoints.erase(it);
            break;
        }
    }
}

/**
* @fn GetClosestCheckPoint
* @brief Get the closest checkpoint from a point using pythagore means no matters the obstacles
*
* @param point : the point from which we want to find the closest checkpoint
* @param checkpoints : the checkpoints we want to check
*
* @return the closest checkpoint to the point
*/
sf::Vector2i Game::GetClosestCheckPoint(const sf::Vector2i& point, std::vector<sf::Vector2i>& checkpoints)
{
    float minDistance = std::numeric_limits<float>::max();
    const sf::Vector2i* closestCheckPoint = nullptr;

    for (const auto& checkPoint : checkpoints)
    {
        const float distance = sqrt(static_cast<float>((checkPoint.x - point.x) * (checkPoint.x - point.x) +
                                       (checkPoint.y - point.y) * (checkPoint.y - point.y)));

        if (distance < minDistance)
        {
            minDistance = distance;
            closestCheckPoint = &checkPoint;
        }
    }

    if (closestCheckPoint)
    {
        return *closestCheckPoint;
    }
    
    return {-1, -1};
}

/**
* @fn ForwardDebug
* @brief Draw the next step of the path
*/
void Game::ForwardDebug()
{
    if (_path.empty() || _CurrentDebugStep + 1 >= _path.size())
    {
        return;
    }

    _CurrentDebugStep++;
    dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(_path.at(_CurrentDebugStep), true);
}

/**
* @fn BackwardDebug
* @brief Draw the previous step of the path
*/
void Game::BackwardDebug()
{
    if (_path.empty() || _CurrentDebugStep < 0)
    {
        return;
    }

    dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(_path.at(_CurrentDebugStep), false);
    _CurrentDebugStep--;
}

/**
* @fn ClearPath
* @brief Clear the path and the debug step
*/
void Game::ClearPath()
{
    _path.clear();
    _CurrentDebugStep = -1;
}

/**
* @fn ResetGame
* @brief  
*/
void Game::ResetGame()
{
    _StartingPoint = {-1,-1};
    _EndingPoint = {-1,-1};
    
    InitGridArray();

    _CheckPoints->clear();
    _Portals->clear();
    _CurrentDebugStep = -1;
    _path.clear();
}

/**
* @fn SetDebugMode
* @brief  
* @param debugMode
*/
void Game::SetDebugMode(bool debugMode)
{
    if ( debugMode )
    {
        _CurrentDebugStep = _path.size() - 1;
    }

    _DebugMode = debugMode;
}

/**
* @fn SetGridArrayItem
* @brief  
* @param column
* @param row
* @param piece
*/
void Game::SetGridArrayItem(const int column, const int row, const GridPieces piece)
{
    if ( column < 0 || column >= NB_COLUMNS || row < 0 || row >= NB_LINES)
    {
        return;
    }
    
    _gridArray[column][row] = piece;
}

/**
* @fn IsDebugMode
* @brief  
* @return 
*/
bool Game::IsDebugMode() const
{
    return _DebugMode;
}