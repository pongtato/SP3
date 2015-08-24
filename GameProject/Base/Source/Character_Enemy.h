#pragma once
#include "Character.h"
#include "TileMap.h"
#include "MyMath.h"

using namespace std;

class CCharacter_Enemy : public CCharacter
{
public:
	CCharacter_Enemy(void);
	~CCharacter_Enemy(void);

	enum DETECTION_VARIABLES
	{
		FOVdistance		= 2,
		FOVArc			= 20,
		ChaseDistance	= 5,
		ScanSpeed		= 50,
		ScanArc			= 45,
		ScanDuration	= 5,
		VARIABLES_TOTAL,
	};

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
		CAMERA,
		FLASHLIGHT,
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
		SCANNING,
		STATE_TOTAL,
	};

	void setMesh(ENEMY_TYPE newMesh);
	void setAmmoType(ENEMY_AMMO_TYPE newAmmoType);
	void setNewState(EMEY_CURRENT_STATE newState);
	bool detectPlayer(Vector3 playerPos);
	void setGroupID(int newGroupID);

	int getMesh(void);
	int getAmmoType(void);
	int getState(void);
	float m_RotationArcMax;
	float m_RotationArcMin;
	int getGroupID(void);

	void Strategy_Chaseplayer(Vector3 playerPos);
	void Strategy_Return(void);
	void Strategy_Scan(double dt);

	Vector3 DetectionCornerL;
	Vector3 DetectionCornerR;
	Vector3 DetectionCornerM;

	void setRotateDirection(Vector3 playerPos);


private:
	ENEMY_TYPE m_enemyMesh;
	ENEMY_AMMO_TYPE m_weaponChoice;
	EMEY_CURRENT_STATE m_enemyState;
	int m_GroupID;
	bool m_RotateDirection;
	float m_MedianRotation;
	float m_ScanTimer;
};
