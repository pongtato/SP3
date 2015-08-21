#pragma once
#include "Weapon.h"

class CRifle : public CWeapon
{
public:
	static CRifle* GetInstance();
private:
	CRifle(void);
	~CRifle(void);

	static CRifle* mInstance;
};
