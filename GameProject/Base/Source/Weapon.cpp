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

void CWeapon::UseAmmo(int Consumption)
{
	Ammo -= Consumption;
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

float CWeapon::GetCooldown(void)
{
	return FireCooldown;
}
int CWeapon::GetDamage(void)
{
	return Damage;
}
float CWeapon::GetFireCooldown(void)
{
	return FireCooldown;
}
