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
	Ammo = 10;
	Damage = 1;
	FireCooldown = 1.0f;
}


CPistol::~CPistol(void)
{

}

