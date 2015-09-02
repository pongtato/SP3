
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	WDamage(0.0f),
	pos(0,0,0),
	timer(0)
{
}

GameObject::~GameObject()
{
}