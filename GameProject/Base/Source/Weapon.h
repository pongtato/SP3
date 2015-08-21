#pragma once
class CWeapon
{
public:
	CWeapon(void);
	~CWeapon(void);

	void SetAmmo(int NewAmmo);
	void UseAmmo(int Consumption);
	void FireCooldownTick(float time);
	void ResetCooldown(void);

	int GetAmmo(void);
	float GetCooldown(void);
	int GetDamage(void);

protected:
	int Ammo;
	int Damage;
	float AttackSpeed;
	float FireCooldown;
};

