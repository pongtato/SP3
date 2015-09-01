#pragma once
class CWeapon
{
public:
	CWeapon(void);
	~CWeapon(void);

	void SetAmmo(int NewAmmo);
	void SetAmmoStored(int NewAmmoStored);
	void UseAmmo(int Consumption);
	void UseableAmmoLeft(int NewAmmoLeft);
	void FireCooldownTick(float time);
	void ResetCooldown(void);

	int GetAmmo(void);
	int GetAmmoStored(void);
	float GetCooldown(void);
	int GetDamage(void);
	float GetFireCooldown(void);
	float GetBulletSpeed(void);

protected:
	int Ammo;
	int AmmoStored;
	int AmmoLeft;
	int Damage;
	float AttackSpeed;
	float FireCooldown;
	float BulletSpeed;
};

