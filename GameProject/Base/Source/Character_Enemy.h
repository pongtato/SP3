#pragma once
#include "Character.h"
#include "TileMap.h"
#include "MyMath.h"
#include "Pathfinding.h"

using namespace std;

class CCharacter_Enemy : public CCharacter
{
public:
	CCharacter_Enemy(void);
	~CCharacter_Enemy(void);

	enum DETECTION_VARIABLES
	{
		FOVdistance		= 5,
		FOVArc			= 20,
		ChaseDistance	= 5,
		ScanSpeed		= 50,
		ScanArc			= 45,
		ScanDuration	= 5,
		MovementDelay	= 2,
		MoveSpeed       = 1,
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
		TRACKING,
		STATE_TOTAL,
	};

	void setMesh(ENEMY_TYPE newMesh);
	void setAmmoType(ENEMY_AMMO_TYPE newAmmoType);
	void setNewState(EMEY_CURRENT_STATE newState);
	bool detectPlayer(Vector3 playerPos, TileMap* tileMap);
	void setGroupID(int newGroupID);

	int getMesh(void);
	int getAmmoType(void);
	int getState(void);
	float m_RotationArcMax;
	float m_RotationArcMin;
	int getGroupID(void);

	void Strategy_Chaseplayer(Vector3 playerPos,TileMap* tileMap);
	void Strategy_Return(void);
	void Strategy_Scan(double dt);
	void Strategy_Stalk(Vector3 playerPos,TileMap* tileMap);

	Vector3 DetectionCornerL;
	Vector3 DetectionCornerR;
	Vector3 DetectionCornerM;
	Vector3 LineOfSight;

	void setRotateDirection(Vector3 playerPos);
	CPathfinding* PATHFIND;

	void UpdateEnemyPosition(double dt);

	TileMap* pathfind_tilemap;
	void CreateGrid(void);
	float MoveDelay;
	vector<CPathfinding_Node*> PathFound;
	void setTargetPosition(Vector3 newTarget);
	Vector3 getTargetPosition(void);
	void resetTimer(void);

private:
	ENEMY_TYPE m_enemyMesh;
	ENEMY_AMMO_TYPE m_weaponChoice;
	EMEY_CURRENT_STATE m_enemyState;
	int m_GroupID;
	bool m_RotateDirection;
	float m_MedianRotation;
	float m_ScanTimer;
	Vector3 TargetPosition;
	int m_CurrentNode;
};
