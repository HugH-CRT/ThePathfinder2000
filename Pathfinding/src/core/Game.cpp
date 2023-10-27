#include "Game.h"
#include "SplashState/SplashState.h"
#include <set>
#include <GameState/GameState.h>

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

Game::~Game()
{
    delete _CheckPoints;
    delete _Portals;
}

std::vector<Pair> Game::AStarAlgorithm(sf::Vector2i startingPoint, sf::Vector2i endingPoint, bool UseDiagonal,
    std::vector<Pair>& _path)
{
    const Pair start = std::make_pair(startingPoint.x, startingPoint.y);
    const Pair dest = std::make_pair(endingPoint.x, endingPoint.y);

    return aStarSearch(start, dest, UseDiagonal, _path);
}

#pragma region AStartAlgorithm

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

/*
 * Brief : Check if the cell is in the bounds of the grid
 *
 * @param row : the row of the cell
 * @param col : the column of the cell
 */
bool Game::IsValid(const int row, const int col)
{
    return (row >= 0) && (row < NB_LINES) && (col >= 0)
        && (col < NB_COLUMNS);
}

/*
 * Brief : Check if the cell is not a wall
 *
 * @param grid : the grid of the game
 */
bool Game::IsNotAWall(const int row, const int col)
{
    if (_gridArray[row][col] != WALL_PIECE)
        return true;

    return false;
}

/*
 * Brief : Check if the cell is the destination
 *
 * @param row : the row of the cell
 * @param col : the column of the cell
 * @param dest : the destination cell
 */
bool Game::IsDestination(const int row, const int col, const Pair dest)
{
    if (row == dest.first && col == dest.second)
        return true;
    
    return false;
}

/*
 * Brief : Calculate the heuristic value
 *
 * @param row : the row of the cell
 * @param col : the column of the cell
 */
double Game::CalculateHValue(const int row, const int col, Pair dest)
{
    return sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second));
}

/*
 * Brief : Trace the path from the destination to the starting point
 *
 * @param cellDetails : the details of the cells
 * @param path : the path to the destination we are building
 */
std::vector<Pair> Game::tracePath(cell cellDetails[][NB_COLUMNS], Pair dest,std::vector<Pair>& path)
{
    int row = dest.first;
    int col = dest.second;

    std::vector<Pair> tempPath;
    
    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col)) {

		if (row != dest.first || col != dest.second) {
            tempPath.emplace_back(row, col);
		}

        const int temp_row = cellDetails[row][col].parent_i;
        const int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;    
    }
    
    tempPath.emplace_back(row, col);

    // Add the starting cell to the path in reverse order
    for (int i = tempPath.size() - 1; i >= 0; i--) {
		path.push_back(tempPath[i]);
	}
    
	return path;
}

/*
 * 
 */
std::vector<Pair> Game::aStarSearch(const Pair startingPoint, const Pair endingPoint, const bool UseDiagonal,std::vector<Pair>& path)
{
    std::vector<Pair> Path;
    
    // If the start is out of range
    if (IsValid(startingPoint.first, startingPoint.second) == false) {
        printf("Source is invalid\n");
        return Path;
    }

    // If the destination is out of range
    if (IsValid(endingPoint.first, endingPoint.second) == false) {
        printf("Destination is invalid\n");
        return Path;
    }

    // Either the source or the destination is blocked
    if (IsNotAWall(startingPoint.first, startingPoint.second) == false
        || IsNotAWall( endingPoint.first, endingPoint.second)
        == false) {
        printf("Source or the destination is blocked\n");
        return Path;
    }

    // If the destination cell is the same as source cell
    if (IsDestination(startingPoint.first, startingPoint.second,endingPoint)
        == true) {
        printf("We are already at the destination\n");
        return Path;
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
            printf("The destination cell is found\n");
            
            return tracePath(cellDetails,endingPoint,path);
        }

        // Marquer le n�ud actuel comme visit�
        closedList[i][j] = true;

        // Parcourir les voisins
        for (int k = 0; k < dx.size(); k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];

            if (IsValid(ni, nj) && !closedList[ni][nj] && IsNotAWall(ni, nj)) {
                double gNew = cellDetails[i][j].g + ((k < 4) ? 1.0 : 1.414);
                double hNew = CalculateHValue(ni, nj,endingPoint);
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
        printf("Failed to find the Destination Cell\n");
    }

	return Path;
}

#pragma endregion AStartAlgorithm

void Game::Play()
{
    _CurrentDebugStep = -1;
    std::vector<sf::Vector2i> tempCheckPoints = *_CheckPoints;
    sf::Vector2i currentPoint = _StartingPoint;

    ClearPath();

    bool AllCheckPointsReached = true;

    if (CheckMapValidity())
    {
        for (int i = 0; i < _CheckPoints->size(); i++)
        {
            std::tuple<sf::Vector2i, bool> result = ProcessNextCheckpoint(tempCheckPoints, currentPoint);

            currentPoint = std::get<sf::Vector2i>(result);
            bool res = std::get<bool>(result);

            if (currentPoint.x == -1 || currentPoint.y == -1) // No path found to next checkpoint
            {
                AllCheckPointsReached = false;
                _path.clear();
                return;
            }

            if ( !res )
            {
                i--;
            }
        }

        if ( AllCheckPointsReached )
        {
            ProcessFinalPath(currentPoint);
        }
    }
}

/*
 * Brief : Process the next checkpoint, Draw the shortest path from the current point to the next checkpoint
 */
std::tuple<sf::Vector2i, bool> Game::ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, sf::Vector2i& currentPoint)
{
    std::vector<Pair> tempPath;
    
    sf::Vector2i closestCheckPoint = PathToClosestCheckPoint(currentPoint,checkpoints, tempPath);

    if ( closestCheckPoint.x == -1 && closestCheckPoint.y == -1) // Means no path to a checkpoint was found
    {
        closestCheckPoint = checkpoints.at(0);
    }
    
    const sf::Vector2i closestPortal = CheckPortalPath(currentPoint, closestCheckPoint, tempPath);
    
    if ( closestCheckPoint.x != -1 && closestCheckPoint.y != -1)
    {
        for (int i = 0; i < checkpoints.size(); i++)
        {
            if (checkpoints[i] == closestCheckPoint)
            {
                checkpoints.erase(checkpoints.begin() + i);
                break;
            }
        }
        
        return {closestCheckPoint, true};
    }
    return {closestPortal, false};
}

/*
 * Draw the final path from the current point to the ending point
 *
 * @param currentPoint : the current point
 */
void Game::ProcessFinalPath(sf::Vector2i& currentPoint)
{
    std::vector<Pair> tempPath;

    GetGame()->AStarAlgorithm( currentPoint, _EndingPoint,_UseDiagonal, tempPath);

    sf::Vector2i closestPortal =  CheckPortalPath(currentPoint, _EndingPoint, tempPath);

    if ( !tempPath.empty() || closestPortal.x != -1 && closestPortal.y != -1)
    {
        DrawPath();
    }
}

/*
 * Brief : Verify if the starting point and the ending point are set
 */
bool Game::CheckMapValidity()
{
    return _StartingPoint.x != -1 && _StartingPoint.y != -1 && _EndingPoint.x != -1 && _EndingPoint.y != -1;
}

/*
 * Brief : Check if the path through a portal is shorter than the base path
 */
sf::Vector2i Game::CheckPortalPath(const sf::Vector2i& currentPoint, sf::Vector2i& nextPoint, const std::vector<Pair>& basePath)
{
    if (!_Portals->empty())
    {
        std::vector<Pair> tempPath;
        
        sf::Vector2i closestPortalStart =  PathToClosestPortal(currentPoint,tempPath); 
        
        std::reverse(tempPath.begin(), tempPath.end());
        
        sf::Vector2i closestPortalNextPoint = PathToClosestPortal(nextPoint,tempPath);

        bool PointFound = closestPortalStart.x != -1 && closestPortalStart.y != -1 && closestPortalNextPoint.x != -1 && closestPortalNextPoint.y != -1; 
  
        if ( PointFound && (tempPath.size() < basePath.size() || basePath.empty() )  && !tempPath.empty())
        {
            for (auto i : tempPath)
            {
                _path.push_back(i);
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

/*
 * Brief : Get the path to the closest portal from a point using the A* algorithm
 *
 * @param point : the point from which we want to find the closest portal
 * @param finalPath : the path to the closest portal we are building
 */
sf::Vector2i Game::PathToClosestPortal(const sf::Vector2i& point,std::vector<Pair>& finalPath)
{
    float minDistance = 99999;
    int minIndex = -1;

    std::vector<Pair> tempPath;

    // Loop through all the portals
    for (int i = 0; i < _Portals->size(); i++)
    {
        std::vector<Pair> fPath;
        const sf::Vector2i currentPoint = _Portals->at(i);
        GetGame()->AStarAlgorithm( currentPoint, point, _UseDiagonal, fPath);

        // If the path is shorter than the current shortest path
        if (fPath.size() < minDistance && !fPath.empty())
        {
            minDistance = fPath.size();
            minIndex = i;
            fPath.erase(fPath.begin());// remove portal as we want to tp not go over it
            tempPath = fPath;
        }
    }

    if ( minIndex != -1 )
    {
        for (auto i : tempPath)
        {
            finalPath.push_back(i);
        }
        return _Portals->at(minIndex);
    }
    return {-1, -1};
}

/*
 * Brief : Get the path to the closest checkpoint from a point using the A* algorithm
 *
 * @param point : the point from which we want to find the closest checkpoint
 * @param checkpoints : the checkpoints we want to check
 * @param finalPath : the path to the closest checkpoint we are building
 */
sf::Vector2i Game::PathToClosestCheckPoint(const sf::Vector2i& point,std::vector<sf::Vector2i>& checkpoints, std::vector<Pair>& finalPath)
{
    float minDistance = 99999;
    int minIndex = -1;

    std::vector<Pair> fPath;

    // Loop through all the checkpoints
    for (int i = 0; i < checkpoints.size(); i++)
    {
        std::vector<Pair> tempPath;
        
        const sf::Vector2i currentPoint = checkpoints.at(i);
        GetGame()->AStarAlgorithm( currentPoint, point, _UseDiagonal, tempPath);

        if (tempPath.empty())
        {
            continue;
        }

        // If the path is shorter than the current shortest path
        if (tempPath.size() < minDistance)
        {
            minDistance = tempPath.size();
            minIndex = i;
            tempPath.erase(tempPath.begin());// remove checkpoint as we dont want to go over it
            fPath = tempPath;
        }
    }

    if ( minIndex != -1 )
    {
        for (int i = fPath.size() - 1; i >= 0; i--)
        {
            finalPath.push_back(fPath[i]);
        }
        return checkpoints.at(minIndex);
    }

    return {-1, -1};
}

/*
 * Brief : Initialize the grid array with empty pieces
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

/*
 * Brief : Draw the path on the grid
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

/*
 * Brief : Draw the next step of the path
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

/*
 * Brief : Draw the previous step of the path
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

/*
 * Brief : Clear the path and the debug step
 */
void Game::ClearPath()
{
    _path.clear();
    _CurrentDebugStep = -1;
}

void Game::ResetGame()
{
    _StartingPoint.x = -1;
    _StartingPoint.y = -1;
    _EndingPoint.x = -1;
    _EndingPoint.y = -1;
    
    InitGridArray();

    _CheckPoints->clear();
    _Portals->clear();
    _CurrentDebugStep = -1;
    _path.clear();
}

#pragma region Setters

void Game::SetDebugMode(bool debugMode)
{
    if ( debugMode )
    {
        _CurrentDebugStep = _path.size() - 1;
    }

    _DebugMode = debugMode;
}

void Game::SetUseDiagonal(bool useDiagonal)
{
    _UseDiagonal = useDiagonal;
}

void Game::SetStartingPoint(sf::Vector2i& startingPoint)
{
    _StartingPoint = startingPoint;
}

void Game::SetEndingPoint(const sf::Vector2i& endingPoint)
{
    _EndingPoint = endingPoint;
}

void Game::SetGridArrayItem(const int column, const int row, const GridPieces piece)
{
    if ( column < 0 || column >= NB_COLUMNS || row < 0 || row >= NB_LINES)
    {
        return;
    }
    
    _gridArray[column][row] = piece;
}

#pragma endregion Setters

#pragma region Getters

bool Game::IsDebugMode() const
{
    return _DebugMode;
}

bool Game::IsUseDiagonal() const
{
    return _UseDiagonal;
}

sf::Vector2i& Game::GetEndingPoint()
{
    return _EndingPoint;
}

std::vector<sf::Vector2i>* Game::GetCheckPoints()
{
    return _CheckPoints;
}

std::vector<sf::Vector2i>* Game::GetPortals()
{
    return _Portals;
}

int Game::GetPathSize()
{
    return _path.size();
}

sf::Vector2i& Game::GetStartingPoint()
{
    return _StartingPoint;
}

#pragma endregion Getters