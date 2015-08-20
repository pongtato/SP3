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

void PlayerWeapon::SetAmmo(int NewAmmo)
{
	Ammo = NewAmmo;
}

void PlayerWeapon::UseAmmo(int Consumption)
{
	Ammo -= Consumption;
}

void PlayerWeapon::FireCooldownTick(float time)
{
	FireCooldown -= time;
}

void PlayerWeapon::ResetCooldown(void)
{
	FireCooldown = AttackSpeed;
}

int PlayerWeapon::GetAmmo(void)
{
	return Ammo;
}

float PlayerWeapon::GetCooldown(void)
{
	return FireCooldown;
}
