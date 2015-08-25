#include "Pathfinding_Grid.h"


CPathfinding_Grid::CPathfinding_Grid(void)
{
	
}


CPathfinding_Grid::~CPathfinding_Grid(void)
{
	for ( unsigned i = 0; i < grid.size(); ++i)
	{
		for ( unsigned j = 0; j < grid[i].size(); ++j)
		{
			delete grid[i][j];
		}
	}
}

void CPathfinding_Grid::createGrid(TileMap* tileMap)
{
	grid.resize(tileMap->getNumOfTilesHeight());
	for ( unsigned i = 0; i < tileMap->getNumOfTilesHeight(); ++i)
	{
		grid[i].resize(tileMap->getNumOfTilesHeight());
		for ( unsigned j = 0; j < tileMap->getNumOfTilesWidth(); ++j)
		{
			CPathfinding_Node* pathfindNode = new CPathfinding_Node;
			grid[i][j] = pathfindNode;
			grid[i][j]->gridX = i;
			grid[i][j]->gridY = j;
			grid[i][j]->m_WorldPosition.Set(i,j,0);

			if ( tileMap->getTile(i,j) != -1 )
			{
				grid[i][j]->m_Walkable = true;
			}
		}
	}
}

CPathfinding_Node* CPathfinding_Grid::getNodeFromWorld(Vector3 Pos)
{
	return grid[Pos.x][Pos.y];
}

vector<CPathfinding_Node*> CPathfinding_Grid::getNeighbours(CPathfinding_Node* node, TileMap* tileMap)
{
	vector<CPathfinding_Node*> neighbours;

	// neighbours
	// (-1,1)  (0,1)  (1,1)
	// (-1,0)  (0,0)  (1,0)
	// (-1,-1) (0,-1) (1,-1)

	// 4 directional
	// (-1,0) (0,1) (1,0) (0,-1)

	//// 8 directional
	//for ( int x = -1; x <= 1; ++x )
	//{
	//	for ( int y = -1; y <=1; ++y )
	//	{
	//		if ( x == 0 && y == 0 )
	//		{
	//			continue;
	//		}
	//	}
	//}

	// 4 directional
	for ( int x = -1; x <= 1; ++x )
	{
		for ( int y = -1; y <= 1; ++y )
		{
			if ( x == 0 && y == 0  || x == -1 && y == -1 || x == -1 && y == 1  || x == 1  && y == -1 || x == 1  && y == 1)
			{
				continue;
			}

			int checkX = node->gridX + x;
			int checkY = node->gridY + y;

			if (checkX >= 0 && checkX < tileMap->getNumOfTilesHeight() && checkY >= 0 && checkY < tileMap->getNumOfTilesWidth())
			{
				neighbours.push_back(grid[checkX][checkY]);
			}
		}
	}

	return neighbours;
}

