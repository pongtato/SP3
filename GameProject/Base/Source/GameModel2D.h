#ifndef GAMEMODEL2D_H

#define GAMEMODEL2D_H


#include "Model.h"

#include "SoundManager.h"
#include "TileMap.h"
#include "Character_Player.h"
#include "Character_Enemy.h"


//Weapons
#include "Pistol.h"
#include "Rifle.h"
#include "Shotgun.h"

#include <vector>

class GameModel2D : public Model
{
public:
	enum COMMANDS {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMP,
		ENTER,
		//Weapon changing
		PREVWEAP,
		NEXTWEAP,
		//Shooting
		SHOOT,
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
		CUBE,

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
	};
	
	Mesh* meshList[TOTAL_GEOMETRY];
	Mesh* weaponList[TOTAL_GUNS];

	TileMap* m_tileMap;
	TileMap* m_ReartileMap;


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
	bool SpawnReady;
	bool newLevel;
	int GroupToSpawn;

	//GameObjects
	std::vector<GameObject *> m_goList;

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
	Mesh* getTileMesh();
	Mesh* getFloorTileMesh();
	Mesh* getWallMesh();

	//Bullet
	Mesh* getBulletMesh();
	void BulletUpdate(double dt);

	void SpawnBullet(int WeaponDamage,Vector3 Velocity);

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
	int AniToUpdate;
	bool ZoomIN;

	//sound
	CSoundManager Sound;
};

#endif