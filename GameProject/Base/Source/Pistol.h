#pragma once
#include "PlayerWeapon.h"

class CPistol : public PlayerWeapon
{
public:
	static CPistol* GetInstance();
private:
	CPistol(void);
	~CPistol(void);

	static CPistol* mInstance;
};
