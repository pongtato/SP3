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
	Ammo = 15;
	AmmoStored = 15;
	Damage = 34;
	FireCooldown = 0.0f;
	AttackSpeed = 0.5f;
	BulletSpeed = 3.f;
}


CRifle::~CRifle(void)
{
}
