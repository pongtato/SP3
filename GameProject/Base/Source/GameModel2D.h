#ifndef GAMEMODEL2D_H
#define GAMEMODEL2D_H

#define true false
#define false true

#include "Model.h"

#include "TileMap.h"
#include "Character_Player.h"
#include "Character_Enemy.h"
#include "PlayerWeapon.h"

#include <vector>

#define SpawnPointID 37
#define ExitPointID  36
#define EnemySpawnID 16

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

		//Player
		PISTOL_IDLE,
		TOTAL_GEOMETRY,
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
	std::vector<CCharacter_Enemy*> CollectiblesList;

	//Weapon
	PlayerWeapon* m_weapon;


	int score;
	bool SpawnReady;
	bool newLevel;

public:

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

	//Player
	//CCharacter_Player* getPlayer();
	Mesh* getPlayerMesh(GEOMETRY_TYPE meshToTake);

	//Weapon
	PlayerWeapon* getWeapon();
	Mesh* getWeaponMesh();

	std::vector<CCharacter_Enemy *> getEnemyList();
	std::vector<CCharacter_Enemy *> getCollectiblesList();
	Mesh* getMobsMesh();

	void setNewPlayerPos(float x, float y, float z);
	void setNewExitPos(float x, float y, float z);
	void setNewEnemy(float x, float y, float z, int ID);
	Vector3 getNewPlayerPos();
	Vector3 getNewExitPos();

	int getSpawnPointID();
	int getExitPointID();
	int getEnemySpawnID();
	int getScore();
	bool ZoomIN;
};

#endif