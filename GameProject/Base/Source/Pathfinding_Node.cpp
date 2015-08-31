#include "Pathfinding_Node.h"


CPathfinding_Node::CPathfinding_Node(void)
{
	m_Walkable = false;
	fCost = 0;
	gCost = 0;
	hCost = 0;
	m_WorldPosition.SetZero();
}


CPathfinding_Node::~CPathfinding_Node(void)
{
}

int CPathfinding_Node::getfCost()
{
	fCost = gCost + hCost;
	return fCost;
}