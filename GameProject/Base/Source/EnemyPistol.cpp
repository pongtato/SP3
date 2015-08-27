#include "EnemyPistol.h"

EPistol* EPistol::mInstance = 0;


EPistol* EPistol::GetInstance()
{
	if (mInstance == 0)
		mInstance = new EPistol();

	return mInstance;
}

EPistol::EPistol(void)
{
	//Unlimited for pistol
	Ammo = 10;
	Damage = 1;
	FireCooldown = 0.0f;
	AttackSpeed = 1.0f;
	BulletSpeed = 2.5f;
}


EPistol::~EPistol(void)
{

}

