#pragma once
#include "PlayerWeapon.h"

class CShotgun : public PlayerWeapon
{
public:
	static CShotgun* GetInstance();
private:
	CShotgun(void);
	~CShotgun(void);

	static CShotgun* mInstance;
};
