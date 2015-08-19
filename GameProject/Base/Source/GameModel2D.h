#ifndef GAMEMODEL2D_H
#define GAMEMODEL2D_H

#include "Model.h"

#include "TileMap.h"
#include "PlayerCharacter.h"
#include "PlayerWeapon.h"

#include <vector>

#define SpawnPointID 37
#define ExitPointID  36

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

protected:
	enum GEOMETRY_TYPE {
		TEXT,
		BACKGROUND,
		TILE,
		TILEFLOOR,
		PLAYER,
		MOBS,
		CROSSHAIR,
		TOTAL_GEOMETRY,
	};
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
	PlayerCharacter *player;
	std::vector<Character *> GuardsList;
	std::vector<Character *> CameraList;
	std::vector<Character *> CollectiblesList;

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
	PlayerCharacter* getPlayer();
	Mesh* getPlayerMesh();

	//Weapon
	PlayerWeapon* getWeapon();
	Mesh* getWeaponMesh();

	std::vector<Character *> getGuardsList();
	std::vector<Character *> getCameraList();
	std::vector<Character *> getCollectiblesList();
	Mesh* getMobsMesh();

	void setNewPlayerPos(float x, float y, float z);
	void setNewExitPos(float x, float y, float z);
	Vector3 getNewPlayerPos();
	Vector3 getNewExitPos();

	int getSpawnPointID();
	int getExitPointID();
	int getScore();
	bool ZoomIN;
};

#endif