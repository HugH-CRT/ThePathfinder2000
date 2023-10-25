#include "Game.h"
#include "SplashState/SplashState.h"
#include <set>

Game::Game(int width, int height, std::string title)
{
	m_data->m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	m_data->machine.AddState(StateRef(new SplashState(this->m_data)));
	Run();
}

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
    if (grid[row][col] != 3)
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
    
    // depart
	//Path.push(make_pair(row, col));

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

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[NB_LINES][NB_COLUMNS];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell
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

    // Définir les mouvements possibles       
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
        
        // Extraire le nœud de la liste ouverte avec le coût "f" le plus bas
        pPair p = *openList.begin();
        openList.erase(openList.begin());

        int i = p.second.first;
        int j = p.second.second;

        // Vérifier si c'est la destination
        if (isDestination(i, j, dest)) {
            printf("The destination cell is found\n");
            
            return tracePath(cellDetails, dest,path);

        }

        // Marquer le nœud actuel comme visité
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
        printf("Failed to find the Destination Cell\n");

	return Path;
}

std::vector<Pair> Game::AStarAlgorithm(int gridArray[NB_LINES][NB_COLUMNS], sf::Vector2i startingPoint, sf::Vector2i endingPoint,bool UseDiagonal, std::vector<Pair>& path)
{
	Pair src = make_pair(startingPoint.x, startingPoint.y);
	Pair dest = make_pair(endingPoint.x, endingPoint.y);

    return aStarSearch(gridArray, src, dest, UseDiagonal,path);
}
