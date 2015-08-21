#pragma once
#include "Weapon.h"

class CShotgun : public CWeapon
{
public:
	static CShotgun* GetInstance();
private:
	CShotgun(void);
	~CShotgun(void);

	static CShotgun* mInstance;
};
