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
	Ammo = 1;
	AmmoStored = 7;
	Damage = 20;
	FireCooldown = 0.0f;
	AttackSpeed = 1.5f;
	BulletSpeed = 2.f;
}


CShotgun::~CShotgun(void)
{
}
