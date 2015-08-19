#ifndef PLAYERWEAPON_H
#define PLAYERWEAPON_H

#include "Vector3.h"
#include "Mesh.h"

class PlayerWeapon
{
private:
	enum WEAPON
	{
		PISTOL,
		SHOTGUN,
		RIFLE,
		END,
	};
	int WeaponState;

public:
	PlayerWeapon();
	~PlayerWeapon();

	int getWeapon();
	void setWeapon(int weapon_type);
};

#endif