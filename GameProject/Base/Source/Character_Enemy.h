#pragma once
#include "Character.h"

class CCharacter_Enemy : public CCharacter
{
public:
	CCharacter_Enemy(void);
	~CCharacter_Enemy(void);

	enum ENEMY_TYPE
	{
		ENEMY_GUARD,
		ENEMY_CAMERA,
		ENEMY_POLICE,
		ENEMY_SWAT,
		ENEMY_BIGBOI,
		ENEMY_TOTAL,
	};

	enum ENEMY_AMMO_TYPE
	{
		PISTOL,
		MG,
		SHOTGUN,
		ROCKET,
		FLASHBANG,
		AMMO_TOTAL,
	};

	enum EMEY_CURRENT_STATE
	{
		IDLE,
		PATROL,
		CHASING,
		ATTACKING,
		RUNNING,
		STATE_TOTAL,
	};

	void setMesh(ENEMY_TYPE newMesh);
	void setAmmoType(ENEMY_AMMO_TYPE newAmmoType);
	void setNewState(EMEY_CURRENT_STATE newState);

	int getMesh(void);
	int getAmmoType(void);
	int getState(void);

private:
	ENEMY_TYPE m_enemyMesh;
	ENEMY_AMMO_TYPE m_weaponChoice;
	EMEY_CURRENT_STATE m_enemyState;
};
