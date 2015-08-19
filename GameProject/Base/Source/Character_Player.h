#pragma once
#include "Character.h"

class CCharacter_Player : public CCharacter
{
public:

	enum PLAYER_TYPE
	{
		PLAYER_MESH_1,
		PLAYER_MESH_2,
		PLAYER_MESH_3,
		PLAYER_MESH_4,
	};

	enum PLAYER_AMMO_TYPE
	{
		PISTOL,
		MG,
		SHOTGUN,
		ROCKET,
		GRENADE,
		AMMO_TOTAL,
	};

	enum PLAYER_CURRENT_STATE
	{
		FLASHED,
		STUNNED,
		WOUNDED,
		STATE_TOTAL,
	};

	void setMesh(PLAYER_TYPE newMesh);
	void setAmmoType(PLAYER_AMMO_TYPE newAmmoType);
	void setNewState(PLAYER_CURRENT_STATE newState);

	int getMesh(void);
	int getAmmoType(void);
	int getState(void);

	static CCharacter_Player* GetInstance();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

private:
	CCharacter_Player(void);
	~CCharacter_Player(void);

	PLAYER_TYPE m_playerMesh;
	PLAYER_AMMO_TYPE m_weaponChoice;
	PLAYER_CURRENT_STATE m_playerState;

	static CCharacter_Player* mInstance;
};

