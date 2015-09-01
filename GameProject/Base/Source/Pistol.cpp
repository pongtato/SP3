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
	Ammo = 1;
	AmmoStored = 6;
	Damage = 100;
	FireCooldown = 0.0f;
	AttackSpeed = 1.0f;
	BulletSpeed = 2.5f;
}


CPistol::~CPistol(void)
{

}

