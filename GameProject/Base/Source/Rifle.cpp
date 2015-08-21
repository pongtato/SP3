#include "Rifle.h"

CRifle* CRifle::mInstance = 0;


CRifle* CRifle::GetInstance()
{
	if (mInstance == 0)
		mInstance = new CRifle();

	return mInstance;
}

CRifle::CRifle(void)
{
	//Unlimited for Rifle
	Ammo = 50;
	Damage = 2;
}


CRifle::~CRifle(void)
{
}
