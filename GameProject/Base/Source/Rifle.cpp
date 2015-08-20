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
	AttackSpeed = 0.2f;
	FireCooldown = 0.0f;
}


CRifle::~CRifle(void)
{
}
