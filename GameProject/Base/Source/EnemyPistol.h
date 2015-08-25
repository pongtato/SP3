#pragma once
#include "Weapon.h"

class EPistol : public CWeapon
{
public:
	static EPistol* GetInstance();
	//int GetDamage();
private:
	EPistol(void);
	~EPistol(void);

	static EPistol* mInstance;
};
