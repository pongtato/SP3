#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon()
:
WeaponState(0)
{
}
PlayerWeapon::~PlayerWeapon()
{

}

int PlayerWeapon::getWeapon()
{
	return WeaponState;
}

void PlayerWeapon::setWeapon(int weapon_type)
{
	this->WeaponState = weapon_type;
}
