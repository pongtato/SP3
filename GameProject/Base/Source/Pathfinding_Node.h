#pragma once
#include "Vector3.h"

using namespace std;

class CPathfinding_Node
{
public:
	CPathfinding_Node(void);
	~CPathfinding_Node(void);

	bool m_Walkable;
	Vector3 m_WorldPosition;
	int gridX, gridY;
	int gCost;
	int hCost;
	int getfCost();

	CPathfinding_Node* Parent;

private:
	int fCost;

};

