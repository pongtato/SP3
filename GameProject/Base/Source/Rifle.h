#pragma once
#include "PlayerWeapon.h"

class CRifle : public PlayerWeapon
{
public:
	static CRifle* GetInstance();
private:
	CRifle(void);
	~CRifle(void);

	static CRifle* mInstance;
};
