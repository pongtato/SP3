#include "Weapon.h"


CWeapon::CWeapon(void)
{
}


CWeapon::~CWeapon(void)
{
}

void CWeapon::SetAmmo(int NewAmmo)
{
	Ammo = NewAmmo;
}

void CWeapon::SetAmmoStored(int NewAmmoStored)
{
	AmmoStored = NewAmmoStored;
}

void CWeapon::UseAmmo(int Consumption)
{
	Ammo -= Consumption;
}

void CWeapon::UseableAmmoLeft(int NewAmmoLeft)
{
	AmmoStored -= NewAmmoLeft;
}

void CWeapon::FireCooldownTick(float time)
{
	FireCooldown -= time;
}

void CWeapon::ResetCooldown(void)
{
	FireCooldown = AttackSpeed;
}

int CWeapon::GetAmmo(void)
{
	return Ammo;
}

int CWeapon::GetAmmoStored(void)
{
	return AmmoStored;
}

float CWeapon::GetCooldown(void)
{
	return FireCooldown;
}
float CWeapon::GetDamage(void)
{
	return Damage;
}
float CWeapon::GetFireCooldown(void)
{
	return FireCooldown;
}

float CWeapon::GetBulletSpeed(void)
{
	return BulletSpeed;
}
