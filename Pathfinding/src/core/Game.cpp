#include "Game.h"
#include "SplashState/SplashState.h"
#include <set>
#include <GameState/GameState.h>

Game::Game(const int width, const int height, const std::string& title) :
    m_UseDiagonal(false)
    , m_DebugMode(false)
    , m_CurrentDebugStep(0)
    , _gridArray{}
    , m_CheckPoints(new std::vector<sf::Vector2i>)
    , m_Portals(new std::vector<sf::Vector2i>)
{
    m_StartingPoint.x = -1;
    m_StartingPoint.y = -1;
    m_EndingPoint.x = -1;
    m_EndingPoint.y = -1;
    
    InitGridArray();

	m_data->m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	m_data->machine.AddState(StateRef(new SplashState(this->m_data)));
}

Game::~Game()
{
    delete m_CheckPoints;
    delete m_Portals;
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
			this->m_data->machine.GetActiveState()->HandleInput();
			this->m_data->machine.GetActiveState()->Update(frameRate);	

			accumulator -= frameRate;
		}

		interpolation = accumulator / frameRate;
		this->m_data->machine.GetActiveState()->Draw(interpolation);
	}
}

bool Game::isValid(int row, int col)
{
    return (row >= 0) && (row < NB_LINES) && (col >= 0)
        && (col < NB_COLUMNS);
}

bool Game::isNotAWall(int grid[][NB_COLUMNS], int row, int col)
{
    if (grid[row][col] != WALL_PIECE)
        return (true);
    else
        return (false);
}

bool Game::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

double Game::calculateHValue(int row, int col, Pair dest)
{
    // Pythagore
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}

std::vector<Pair>  Game::tracePath(cell cellDetails[][NB_COLUMNS], Pair dest, std::vector<Pair>& path)
{
    int row = dest.first;
    int col = dest.second;

    std::vector<Pair> tempPath;

    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col)) {

		if (row != dest.first || col != dest.second) {
            tempPath.push_back(make_pair(row, col));
		}

        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;    
    }

    for (int i = tempPath.size() - 1; i >= 0; i--) {
		path.push_back(tempPath[i]);
	}
    
	return path;
}

std::vector<Pair> Game::aStarSearch(int grid[][NB_COLUMNS], Pair src, Pair dest, bool UseDiagonal,std::vector<Pair>& path)
{
    std::vector<Pair> Path;
    
    // If the start is out of range
    if (isValid(src.first, src.second) == false) {
        printf("Source is invalid\n");
        return Path;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == false) {
        printf("Destination is invalid\n");
        return Path;
    }

    // Either the source or the destination is blocked
    if (isNotAWall(grid, src.first, src.second) == false
        || isNotAWall(grid, dest.first, dest.second)
        == false) {
        printf("Source or the destination is blocked\n");
        return Path;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)
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
    i = src.first, j = src.second;
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
    std::vector<int> dx = { -1, 1, 0, 0 };
    std::vector<int> dy = { 0, 0, 1, -1 };

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
        if (isDestination(i, j, dest)) {
            printf("The destination cell is found\n");
            
            return tracePath(cellDetails, dest,path);

        }

        // Marquer le n�ud actuel comme visit�
        closedList[i][j] = true;

        // Parcourir les voisins
        for (int k = 0; k < dx.size(); k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];

            if (isValid(ni, nj) && !closedList[ni][nj] && isNotAWall(grid, ni, nj)) {
                double gNew = cellDetails[i][j].g + ((k < 4) ? 1.0 : 1.414);
                double hNew = calculateHValue(ni, nj, dest);
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

std::vector<Pair> Game::AStarAlgorithm(int gridArray[NB_LINES][NB_COLUMNS], sf::Vector2i startingPoint, sf::Vector2i endingPoint,bool UseDiagonal, std::vector<Pair>& path)
{
	Pair src = make_pair(startingPoint.x, startingPoint.y);
	Pair dest = make_pair(endingPoint.x, endingPoint.y);

    return aStarSearch(gridArray, src, dest, UseDiagonal,path);
}

#pragma endregion AStartAlgorithm

void Game::Play()
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
}

sf::Vector2i Game::ProcessNextCheckpoint(std::vector<sf::Vector2i>& checkpoints, sf::Vector2i& currentPoint)
{
    sf::Vector2i closestCheckpoint = checkpoints[0];

    int pathLength = _path.size();
    std::vector<Pair> tempPath;

    GetGame()->AStarAlgorithm(_gridArray, currentPoint, closestCheckpoint, m_UseDiagonal, tempPath);

    if (pathLength == tempPath.size())
    {
        return sf::Vector2i(-1, -1);
    }

    CheckPortalPath(currentPoint, closestCheckpoint, tempPath);

    if (!m_DebugMode)
    {
        for (auto& i : _path)
        {
            dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(i, false);
        }
    }

    checkpoints.erase(checkpoints.begin());

    return closestCheckpoint;
}

void Game::ProcessFinalPath(sf::Vector2i& currentPoint)
{
    std::vector<Pair> tempPath;

    GetGame()->AStarAlgorithm(_gridArray, currentPoint, m_EndingPoint, m_UseDiagonal, tempPath);

    CheckPortalPath(currentPoint, m_EndingPoint, tempPath);

    if (!m_DebugMode)
    {
        for (auto& i : _path)
        {
            dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(i, true);
        }
    }
}

bool Game::CheckMapValidity()
{
    return m_StartingPoint.x != -1 && m_StartingPoint.y != -1 && m_EndingPoint.x != -1 && m_EndingPoint.y != -1;
}

void Game::CheckPortalPath(sf::Vector2i& currentPoint, sf::Vector2i& nextPoint, const std::vector<Pair>& basePath)
{
    if (!m_Portals->empty())
    {
        std::vector<Pair> tempPath;
        GetGame()->AStarAlgorithm(_gridArray, currentPoint, GetClosestPortal(currentPoint), m_UseDiagonal, tempPath);
        GetGame()->AStarAlgorithm(_gridArray, nextPoint, GetClosestPortal(nextPoint), m_UseDiagonal, tempPath);

        if (tempPath.size() < basePath.size())
        {
            for (auto i : tempPath)
            {
                _path.push_back(i);
            }
            return;
        }
    }

    for (auto i : basePath)
    {
        _path.push_back(i);
    }
}

sf::Vector2i& Game::GetClosestPortal(sf::Vector2i& point)
{
    float minDistance = 99999;
    int minIndex = -1;

    for (int i = 0; i < m_Portals->size(); i++)
    {
        std::vector<Pair> tempPath;

        sf::Vector2i currentPoint = m_Portals->at(i);
        GetGame()->AStarAlgorithm(_gridArray, currentPoint, point, m_UseDiagonal, tempPath);

        if (tempPath.empty())
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

void Game::ForwardDebug()
{
    if (_path.empty() || m_CurrentDebugStep + 1 >= _path.size())
    {
        return;
    }

    m_CurrentDebugStep++;
    dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(_path.at(m_CurrentDebugStep), true);
}

void Game::BackwardDebug()
{
    if (_path.empty() || m_CurrentDebugStep < 0)
    {
        return;
    }

    dynamic_cast<GameState*>(m_data->machine.GetActiveState().get())->DrawStepPath(_path.at(m_CurrentDebugStep), false);
    m_CurrentDebugStep--;
}

void Game::ClearPath()
{
    _path.clear();
    m_CurrentDebugStep = -1;
}

#pragma region Setters

void Game::SetDebugMode(bool debugMode)
{
    if ( debugMode )
    {
        m_CurrentDebugStep = _path.size() - 1;
    }

    m_DebugMode = debugMode;
}

void Game::SetUseDiagonal(bool useDiagonal)
{
    m_UseDiagonal = useDiagonal;
}

void Game::SetStartingPoint(sf::Vector2i& startingPoint)
{
    m_StartingPoint = startingPoint;
}

void Game::SetEndingPoint(const sf::Vector2i& endingPoint)
{
    m_EndingPoint = endingPoint;
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
    return m_DebugMode;
}

bool Game::IsUseDiagonal() const
{
    return m_UseDiagonal;
}

sf::Vector2i& Game::GetEndingPoint()
{
    return m_EndingPoint;
}

std::vector<sf::Vector2i>* Game::GetCheckPoints()
{
    return m_CheckPoints;
}

std::vector<sf::Vector2i>* Game::GetPortals()
{
    return m_Portals;
}

int Game::GetPathSize()
{
    return _path.size();
}

sf::Vector2i& Game::GetStartingPoint()
{
    return m_StartingPoint;
}

#pragma endregion Getters