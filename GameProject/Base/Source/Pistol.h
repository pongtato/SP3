#pragma once
#include "Weapon.h"

class CPistol : public CWeapon
{
public:
	static CPistol* GetInstance();
	//int GetDamage();
private:
	CPistol(void);
	~CPistol(void);

	static CPistol* mInstance;
};
