#include "Shotgun.h"

CShotgun* CShotgun::mInstance = 0;


CShotgun* CShotgun::GetInstance()
{
	if (mInstance == 0)
		mInstance = new CShotgun();

	return mInstance;
}

CShotgun::CShotgun(void)
{
	//Unlimited for Shotgun
	Ammo = 70;
	Damage = 2;
	AttackSpeed = 1.0f;
	FireCooldown = 0.5f;
}


CShotgun::~CShotgun(void)
{
}
