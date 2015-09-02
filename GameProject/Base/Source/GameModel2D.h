#ifndef GAMEMODEL2D_H

#define GAMEMODEL2D_H


#include "Model.h"
#include <ctime>
#include "SoundManager.h"
#include "TileMap.h"
#include "Character_Player.h"
#include "Character_Enemy.h"


//Weapons
#include "Pistol.h"
#include "Rifle.h"
#include "Shotgun.h"

#include <vector>
#include <fstream>

class GameModel2D : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		UNLOCK,
		ENTER,
		CHECK,
		ESCAPE,
		//Weapon changing
		PREVWEAP,
		NEXTWEAP,
		WEAPON1,
		WEAPON2,
		WEAPON3,
		//Shooting
		SHOOT,
		//Reload
		RELOAD,
		INTERACT,
		NUM_COMMANDS,
	};

	enum GEOMETRY_TYPE {
		TEXT,
		BACKGROUND,
		TILE,
		TILEFLOOR,
		PLAYER,
		MOBS,
		CROSSHAIR,
		BULLET,
		EBULLET,
		CUBE,
		TEXT_PROMPT,
		HEALTH,
		HEALTH_DYING,
		HEALTH_BAR,
		PISTOL_ICON,
		PISTOL_AMMO,
		RIFLE_ICON,
		RIFLE_AMMO,
		SHOTGUN_ICON,
		SHOTGUN_AMMO,
		FOG,
		EXPLORED_FOG,
		KEY,
		TIMER_ICON,
		WIN,
		LOSE,

		//Player
		PISTOL_IDLE,
		PISTOL_RELOAD,
		PISTOL_SHOOT,
		RIFLE_IDLE,
		RIFLE_RELOAD,
		RIFLE_SHOOT,
		SHOTGUN_IDLE,
		SHOTGUN_RELOAD,
		SHOTGUN_SHOOT,
		PLAYER_RADIUS,
		PLAYER_UNDETECTED,
		PLAYER_DETECTED,
		PLAYER_CAUTION,
		//Enemy
		ALERT,
		CAUTION,
		ENEMY_LIGHT_IDLE,
		ENEMY_CAMERA,
		BOSS,
		CAR_RED,
		CAR_BLUE,
		CAR_YELLOW,
		CAR_GREEN,
		ENEMY_CONE,

		//Lock Pick
		LOCKPICKBG,
		LOCKPICKBAR,
		LOCKPICKBALL,

		TOTAL_GEOMETRY,
	};

	enum TILE_IDS
	{
		SPAWN_ID		= 37,
		EXIT_ID			= 36,
		ENEMY_ID		= 16,
		CAMERA_ID		= 38,
		SAVE_ID			= 44,
		PC_ID			= 39,
		AMMO_ID			= 40,
		LOCKPICK_ID_2	= 41,
		LOCKPICK_ID_1	= 42,
		KEYUNLOCK_ID	= 43,
		KEY_ID			= 17,
		LASER_HORI_ID	= 18,
		LASER_VERTI_ID	= 19,
		BOSS_ID			= 61,
		CAR_BLUE_ID		= 62,
		CAR_GREEN_ID	= 63,
		CAR_RED_ID		= 64,
		CAR_YELLOW_ID	= 65,
		BAGGAGE			= 66,
		CAR_BLUE_S		= 67,
		CAR_GREEN_S		= 68,
		CAR_RED_S		= 69,
		CAR_YELLOW_S	= 70,
		TOTAL_ID,
	};

protected:
	enum WEAPON_TYPE
	{
		PISTOL,
		SHOTGUN,
		RIFLE,
		TOTAL_GUNS,
	}; float WeaponChangeCooldown;
	
	Mesh* meshList[TOTAL_GEOMETRY];
	Mesh* weaponList[TOTAL_GUNS];

	TileMap* m_tileMap;
	TileMap* m_ReartileMap;
	TileMap* m_AItilemap;

	//Player spawn point read from text file
	Vector3 newPlayerPos;
	//Exit point read from text file
	Vector3 newExitPos;

	//Player
	std::vector<CCharacter_Enemy*> EnemyList;
	std::vector<GameObject*> CollectiblesList;
	std::vector<GameObject*> InteractionList;
	//GameObjects
	std::vector<GameObject *> m_goList;
	std::vector<GameObject *> m_checkingList;
	std::vector<GameObject *> m_fogList;
	std::vector<GameObject *> m_fogCheckerList;


	int score;
	int bulletUsed;
	int CDTimer;
	int CDTimerLimit;
	bool SpawnReady;
	bool newLevel;
	bool m_ObjectiveCleared;
	int GroupToSpawn;
	float FPS;

	int ammoInPistol;
	int ammoInRifle;
	int ammoInShotgun;

	//Lock Key
	int KEYCOUNT;
	//Computer Laser
	bool LaserActive;
	//Lock Picking
	bool InLockPick1;
	bool InLockPick2;
	float LockPickY;
	bool LockPickUp;
	float LockPickBoxTop1;
	float LockPickBoxBtm1;
	float LockPickBoxTop2;
	float LockPickBoxBtm2;
	bool nearLockPick;

	//limit walking
	int walkingSoundLimit;

	Model levelSet;

public:
	//Collision
	void LaserCollisionCheck(double dt);
	void KeyCollisionCheck(double dt);
	void LockCollisionCheck(double dt);
	void ExitCollisionCheck(double dt);
	void ComputerCollisionCheck(double dt);
	void LockPickCollisionCheck(double dt);
	//Weapon update
	void WeaponShooting(double dt);
	void WeaponReload(double dt);
	void WeaponChanging(double dt);
	//Lock Picking
	bool getLockPick1();
	bool getLockPick2();
	bool getNearLock();
	bool hasReadLoc;
	Mesh* getLockPickBG();
	Mesh* getLockPickBar();
	Mesh* getLockPickBall();
	float getLockPickY();
	float Lv2Objective;
	float Lv2ObjectiveCompare;
	
	int AniToUpdate;
	bool ZoomIN;
	int m_CurrentLevel;
	int m_EnemySpawnCount;

	Mesh* getTextMesh();
	Mesh* getBackgroundMesh();
	//Crosshair
	Mesh* getCrosshairMesh();
	TileMap* getTileMap();
	TileMap* getRearTileMap();
	TileMap* getAITileMap();
	Mesh* getTileMesh();
	Mesh* getFloorTileMesh();
	Mesh* getWallMesh();
	//Bullet
	Mesh* getBulletMesh();
	Mesh* getEBulletMesh();
	//Gameobjects
	GameObject* FetchGO();
	std::vector<GameObject *> getGameObjectList();
	//Player
	Mesh* getPlayerMesh(GEOMETRY_TYPE meshToTake);
	//Enemy
	Mesh* getEnemyMesh(GEOMETRY_TYPE meshToTake);
	//CAR
	Mesh* getCarMesh(GEOMETRY_TYPE meshToTake);
	//mehs taker
	Mesh* getMeshTaker(GEOMETRY_TYPE meshToTake);
	//Weapon
	Mesh* getWeaponMesh();
	//Guards, camera
	std::vector<CCharacter_Enemy *> getEnemyList();
	//Ammo, key, save
	std::vector<GameObject *> getCollectiblesList();
	//PC, locks
	std::vector<GameObject *> getInteractionList();
	//fog_list
	std::vector<GameObject *> getFogList();
	std::vector<GameObject *> getFogCheckerList();

	//Player face
	Mesh* getPlayerFace();
	//Keys
	Mesh* getKeys();
	//Timer
	Mesh* getCountDownTimerIcon();
	Mesh* getMobsMesh();
	//Text Prompts
	Mesh* getTextPrompt();
	//Health Bar
	Mesh* getHealth();
	Mesh* getHealthDying();
	Mesh* getHealthBar();
	//Weapon Icon
	Mesh* getPistolIcon();
	Mesh* getRifleIcon();
	Mesh* getShotgunIcon();
	//Weapon Ammo
	Mesh* getPistolAmmo();
	Mesh* getRifleAmmo();
	Mesh* getShotgunAmmo();
	Mesh* getFogOfWar();
	Mesh* getExploredFogOfWar();
	Mesh* getPlayerRadius();

	void setNewPlayerPos(float x, float y, float z);
	void setNewExitPos(float x, float y, float z);
	void setNewEnemy(float x, float y, float z, int ID);
	void setNewCollectible(Vector3 Pos,Vector3 Scale,GameObject::GAMEOBJECT_TYPE type, int spriteCol, int spriteRow);
	void setNewInteraction(Vector3 Pos,Vector3 Scale,GameObject::GAMEOBJECT_TYPE type, int spriteCol, int spriteRow);
	void getMapData();
	void BulletUpdate(double dt);
	int VeryRealRaycasting(double dt);
	void GhettoFogOfWar(void);
	void FogUpdate(double dt);
	void SpawnBullet(float WeaponDamage,float Speed, double dt);
	void SpawnSGBullets(float WeaponDamage, float Speed, double dt);
	void SpawnEnemyBullet(Vector3 EnemyPos, Vector3 Vel);
	//void checkCollision(float x, float y, float z, float scale, float VelX, float VelY, float VelZ, GameObject* go2);
	bool checkCollision(Vector3 Pos, Vector3 scale, Vector3 Vel, GameObject* go2, double dt);
	Vector3 getNewPlayerPos();
	Vector3 getNewExitPos();
	int getScore();
	int getCDTimer();
	int getKeyCount();
	float getFPS();
	bool isZoomed;
	bool m_resultScreen;
	bool m_GameLost;
	//sound
	CSoundManager Sound;
	virtual void Init();
	virtual void Update(double dt);
	void setCommands(int command);
	void getOffset(float& mapOffset_x, float& mapOffset_y);
	void cameraZoom(double dt);
	void objective(void);
	bool getObjectiveCleared(void);
	void EnemyDecision(double dt);
	bool CollideWorldObject(TILE_IDS id,GameObject::GAMEOBJECT_TYPE goType,double dt);
	void LockPicking(double dt);
	void BulletHandle(double dt);
	void GameEnd();


};

#endif