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
//Enemy Weapons
#include "EnemyPistol.h"

#include <vector>

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
		//Weapon changing
		PREVWEAP,
		NEXTWEAP,
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
		HEALTH_BAR,

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

		//Enemy
		ALERT,
		CAUTION,
		ENEMY_LIGHT_IDLE,
		ENEMY_CAMERA,
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


	//float m_mapOffset_x;
	//float m_mapOffset_y;

	//Player
	//CCharacter_Player *player;
	std::vector<CCharacter_Enemy*> EnemyList;
	std::vector<GameObject*> CollectiblesList;
	std::vector<GameObject*> InteractionList;

	//Weapon
	//PlayerWeapon* m_weapon;


	int score;
	int CDTimer;
	int CDTimerLimit;
	bool SpawnReady;
	bool newLevel;
	int GroupToSpawn;
	float FPS;

	//Lock Key
	int KEYCOUNT;
	//Computer Laser
	bool LaserActive;
	//Lock Picking
	bool InLockPick;
	float LockPickY;
	bool LockPickUp;
	float LockPickBoxTop;
	float LockPickBoxBtm;

	//GameObjects
	std::vector<GameObject *> m_goList;
	std::vector<GameObject *> m_checkingList;

public:

	bool hasReadLoc;

	virtual void Init();
	virtual void Update(double dt);

	void setCommands(int command);

	Mesh* getTextMesh();
	Mesh* getBackgroundMesh();
	//Crosshair
	Mesh* getCrosshairMesh();

	void getOffset(float& mapOffset_x, float& mapOffset_y);
	TileMap* getTileMap();
	TileMap* getRearTileMap();
	TileMap* getAITileMap();
	Mesh* getTileMesh();
	Mesh* getFloorTileMesh();
	Mesh* getWallMesh();

	//Bullet
	Mesh* getBulletMesh();
	Mesh* getEBulletMesh();
	void BulletUpdate(double dt);

	void SpawnBullet(int WeaponDamage,float Speed);
	void SpawnSGBullets(int WeaponDamage, float Speed);
	void SpawnEnemyBullet(Vector3 EnemyPos, Vector3 Vel);

	//Gameobjects
	GameObject* FetchGO();
	std::vector<GameObject *> getGameObjectList();

	//Player
	Mesh* getPlayerMesh(GEOMETRY_TYPE meshToTake);

	//Enemy
	Mesh* getEnemyMesh(GEOMETRY_TYPE meshToTake);

	//Weapon
	Mesh* getWeaponMesh();

	//Guards, camera
	std::vector<CCharacter_Enemy *> getEnemyList();
	//Ammo, key, save
	std::vector<GameObject *> getCollectiblesList();
	//PC, locks
	std::vector<GameObject *> getInteractionList();
	Mesh* getMobsMesh();

	//Text Prompts
	Mesh* getTextPrompt();

	//Health Bar
	Mesh* getHealth();
	Mesh* getHealthBar();

	void setNewPlayerPos(float x, float y, float z);
	void setNewExitPos(float x, float y, float z);
	void setNewEnemy(float x, float y, float z, int ID);
	void setNewCollectible(Vector3 Pos,Vector3 Scale,GameObject::GAMEOBJECT_TYPE type, int spriteCol, int spriteRow);
	void setNewInteraction(Vector3 Pos,Vector3 Scale,GameObject::GAMEOBJECT_TYPE type, int spriteCol, int spriteRow);
	void getMapData();

	//void checkCollision(float x, float y, float z, float scale, float VelX, float VelY, float VelZ, GameObject* go2);
	bool checkCollision(Vector3 Pos, Vector3 scale, Vector3 Vel, GameObject* go2, double dt);

	Vector3 getNewPlayerPos();
	Vector3 getNewExitPos();
	int getScore();
	int getCDTimer();
	int AniToUpdate;
	bool ZoomIN;
	float getFPS();
	int m_CurrentLevel;
	int m_EnemySpawnCount;

	//sound
	CSoundManager Sound;
};

#endif