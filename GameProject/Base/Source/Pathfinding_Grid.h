#pragma once
#include <vector>
#include "Vector2.h"
#include "Pathfinding_Node.h"
#include "TileMap.h"
#include <cmath>

using namespace std;

class CPathfinding_Grid
{
public:
	CPathfinding_Grid(void);
	~CPathfinding_Grid(void);

	Vector2 gridWorldSize;

	vector<vector<CPathfinding_Node*>> grid;
	void createGrid(TileMap* tileMap);
	CPathfinding_Node* getNodeFromWorld(Vector3 Pos);
	vector<CPathfinding_Node*> getNeighbours(CPathfinding_Node* node, TileMap* tileMap);
};

