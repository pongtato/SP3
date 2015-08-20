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
protected:
	int Ammo;
	int Damage;
	float AttackSpeed;
	float FireCooldown;
public:
	PlayerWeapon();
	~PlayerWeapon();

	int getWeapon();
	void setWeapon(int weapon_type);

	void SetAmmo(int NewAmmo);
	void UseAmmo(int Consumption);
	void FireCooldownTick(float time);
	void ResetCooldown(void);

	int GetAmmo(void);
	float GetCooldown(void);
};

#endif