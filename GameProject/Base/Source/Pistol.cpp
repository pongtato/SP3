#include "Pistol.h"

CPistol* CPistol::mInstance = 0;


CPistol* CPistol::GetInstance()
{
	if (mInstance == 0)
		mInstance = new CPistol();

	return mInstance;
}

CPistol::CPistol(void)
{
	//Unlimited for pistol
	Ammo = -1;
	Damage = 1;
	AttackSpeed = 1.0f;
	FireCooldown = 0.0f;
}


CPistol::~CPistol(void)
{
}
