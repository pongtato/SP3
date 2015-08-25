#pragma once
#include "Vector3.h"
#include "Pathfinding_Grid.h"
#include "Pathfinding_Node.h"
#include <algorithm>

using namespace std;

class CPathfinding
{
public:
	CPathfinding(void);
	~CPathfinding(void);

	CPathfinding_Grid* pathfinding_grid;
	vector<CPathfinding_Node*> FindPath(Vector3 startPos, Vector3 targetPos, TileMap* tileMap);
	int getDistance(CPathfinding_Node* nodeA,CPathfinding_Node* nodeB);
	vector<CPathfinding_Node*> RetracePath(CPathfinding_Node* startNode, CPathfinding_Node* endNode);
	void Init(TileMap* tileMap);
};

