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
		PathfindMS_multiplier = 1,
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
		CHECKING,
		STATE_TOTAL,
	};

	enum PATROL_MOVE_STATE
	{
		PATROL_UP,
		PATROL_DOWN,
		PATROL_LEFT,
		PATROL_RIGHT,
		TOTAL_PATROL_STATES,
	};

	enum CAMERA_SCAN_STATE
	{
		// 270 ~ 90 DEG
		ULUR,
		// 0 ~ 180 DEG
		URBR,
		// 90 ~ 270 DEG
		BRBL,
		// 180 ~ 360 DEG
		BLUL,
		TOTAL_CAMERA_STATES,
	};

	void setMesh(ENEMY_TYPE newMesh);
	void setAmmoType(ENEMY_AMMO_TYPE newAmmoType);
	void setNewState(EMEY_CURRENT_STATE newState);
	void setPatrolState(PATROL_MOVE_STATE newState);
	void setCameraState(CAMERA_SCAN_STATE newState);
	bool detectPlayer(Vector3 playerPos, TileMap* tileMap);
	void setGroupID(int newGroupID);

	int getMesh(void);
	int getAmmoType(void);
	int getState(void);
	int getPatrolState(void);
	int getCameraState(void);
	float m_RotationArcMax;
	float m_RotationArcMin;
	int getGroupID(void);

	void Strategy_Chaseplayer(Vector3 playerPos,TileMap* tileMap);
	void Strategy_Return(void);
	void Strategy_Scan(double dt);
	bool Strategy_Pathfind(Vector3 playerPos,TileMap* tileMap);
	void Strategy_Track(double dt);
	void Strategy_Patrol(double dt);
	void Strategy_Camera(double dt);

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

	bool InLineOfSight;

	void setCameraDelay(float newDelay);

private:
	ENEMY_TYPE m_enemyMesh;
	ENEMY_AMMO_TYPE m_weaponChoice;
	EMEY_CURRENT_STATE m_enemyState;
	PATROL_MOVE_STATE m_patrolState;
	CAMERA_SCAN_STATE m_cameraState;
	int m_GroupID;
	bool m_RotateDirection;
	float m_MedianRotation;
	float m_ScanTimer;
	Vector3 TargetPosition;
	int m_CurrentNode;
	float m_CameraDelay;
	float m_CameraDelayReset;
	bool delayTicking;
	float m_RotationCompare;
};
