#include "Pathfinding.h"


CPathfinding::CPathfinding(void)
{
}


CPathfinding::~CPathfinding(void)
{
	delete pathfinding_grid;
}

void CPathfinding::Init(TileMap* tileMap)
{
	pathfinding_grid = new CPathfinding_Grid;
	pathfinding_grid->createGrid(tileMap);
}

vector<CPathfinding_Node*> CPathfinding::FindPath(Vector3 startPos, Vector3 targetPos, TileMap* tileMap)
{
	CPathfinding_Node* startNode = pathfinding_grid->getNodeFromWorld(startPos);
	CPathfinding_Node* targetNode = pathfinding_grid->getNodeFromWorld(targetPos);

	vector<CPathfinding_Node*> openSet;
	vector<CPathfinding_Node*> closedSet;

	openSet.push_back(startNode);

	while ( openSet.size() > 0 )
	{
		CPathfinding_Node* currentNode = openSet[0];
		for ( int i = 0; i < openSet.size(); ++i)
		{
			if (openSet[i]->getfCost() < currentNode->getfCost() || (openSet[i]->getfCost() == currentNode->getfCost() && openSet[i]->hCost < currentNode->hCost) )
			{
				currentNode = openSet[i];
			}
		}

		openSet.erase(remove(openSet.begin(),openSet.end(),currentNode),openSet.end());
		closedSet.push_back(currentNode);

		if ( currentNode == targetNode )
		{
			openSet.clear();
			closedSet.clear();
			return RetracePath(startNode,targetNode);
		}

		vector<CPathfinding_Node*> neighbour = pathfinding_grid->getNeighbours(currentNode,tileMap);

		for ( int i = 0; i  < neighbour.size(); ++i )
		{
			if ( !neighbour[i]->m_Walkable || find(closedSet.begin(),closedSet.end(),neighbour[i]) != closedSet.end() )
			{
				continue;
			}

			int newMovementCostToNeighbour = currentNode->gCost + getDistance(currentNode,neighbour[i]);

			if ( newMovementCostToNeighbour < neighbour[i]->gCost || !(find(openSet.begin(),openSet.end(),neighbour[i]) != openSet.end()))
			{
				neighbour[i]->gCost = newMovementCostToNeighbour;
				neighbour[i]->hCost = getDistance(neighbour[i], targetNode);
				neighbour[i]->Parent = currentNode;

				if ( !(find(openSet.begin(),openSet.end(),neighbour[i]) != openSet.end()))
				{
					openSet.push_back(neighbour[i]);
				}
			}
		}
	}
}

int CPathfinding::getDistance(CPathfinding_Node* nodeA,CPathfinding_Node* nodeB)
{
	int distX = abs(nodeA->gridX - nodeB->gridX);
	int distY = abs(nodeA->gridY - nodeB->gridY);

	if (distX > distY)
	{
		return 14*distY + 10*(distX-distY);
	}
	else
	{
		return 14*distX + 10*(distY-distX);
	}
}

vector<CPathfinding_Node*> CPathfinding::RetracePath(CPathfinding_Node* startNode, CPathfinding_Node* endNode)
{
	vector<CPathfinding_Node*> path;
	CPathfinding_Node* currentNode = endNode;

	while (currentNode != startNode)
	{
		path.push_back(currentNode);
		currentNode = currentNode->Parent;
	}
	reverse(path.begin(),path.end());

	return path;
}
