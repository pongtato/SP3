#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BULLET,
		GO_EBULLET,
		GO_WALL,
		GO_SAVE,
		GO_PC,
		GO_AMMO,
		GO_LOCKPICK_2,
		GO_LOCKPICK_1,
		GO_LOCK_KEY_ID,
		GO_KEY_ID,
		GO_LASER_HORI,
		GO_LASER_VERTI,
		GO_EXIT,
		GO_FOG,
		GO_EXPLORED_FOG,
		GO_BAGGAGE,
		GO_BLUE,
		GO_GREEN,
		GO_RED,
		GO_YELLOW,
		GO_BLUE_CAR,
		GO_GREEN_CAR,
		GO_RED_CAR,
		GO_YELLOW_CAR,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 dir;
	Vector3 normal;
	Vector3 acc;
	bool active;
	float mass;
	float angleOrientation;
	int ID;
	float WDamage;
	int SpriteRow;
	int SpriteColumn;
	float timer;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BULLET);
	~GameObject();
};

#endif