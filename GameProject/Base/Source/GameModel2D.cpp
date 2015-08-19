#include "GameModel2D.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

#include "Character_Enemy.h"

const float m_worldHeight = 120;
const float m_worldWidth = 160;

void GameModel2D::Init()
{
	Model::Init();
	camera.Init(Vector3(20, 15, 50), Vector3(20, 15, 0), Vector3(0, 1, 0));
	for (int count = 0; count < GEOMETRY_TYPE::TOTAL_GEOMETRY; ++count)
	{
		meshList[count] = new Mesh("null");
		meshList[count]->textureID[0] = 0;
	}
	meshList[TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[TEXT]->textureID[0] = LoadTGA("Image//Font.tga");
	meshList[BACKGROUND] = MeshBuilder::GenerateQuad("background", Color());
	meshList[BACKGROUND]->textureID[0] = LoadTGA("Image\\background.tga");
	meshList[TILE] = MeshBuilder::GenerateText("tile", 12, 5);
	meshList[TILE]->textureID[0] = LoadTGA("Image\\Maps\\World.tga");
	meshList[TILEFLOOR] = MeshBuilder::GenerateText("tile", 12, 5);
	meshList[TILEFLOOR]->textureID[0] = LoadTGA("Image\\Maps\\World.tga");
	meshList[PLAYER] = MeshBuilder::GenerateText("player", 8, 16);
	meshList[PLAYER]->textureID[0] = LoadTGA("Image//Player.tga");
	meshList[MOBS] = MeshBuilder::GenerateText("mobs", 4, 4);
	meshList[MOBS]->textureID[0] = LoadTGA("Image//mobs.tga");
	meshList[CROSSHAIR] = MeshBuilder::GenerateQuad("Crosshair", Color());
	meshList[CROSSHAIR]->textureID[0] = LoadTGA("Image\\Crosshair.tga");

	//Player
	meshList[PISTOL_IDLE] = MeshBuilder::GenerateText("PISTOL_IDLE", 1, 20);
	meshList[PISTOL_IDLE]->textureID[0] = LoadTGA("Image\\Player\\PISTOL_IDLE.tga");

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	//m_mapOffset_x = 0;
	//m_mapOffset_y = 0;
	
	newPlayerPos.Set(0,0,0);
	newExitPos.Set(0,0,0);
	score = 0;
	ZoomIN = false;
	SpawnReady = false;
	newLevel = false;
}

void GameModel2D::Update(double dt)
{
	if (commands[MOVE_UP]) CCharacter_Player::GetInstance()->moveUp();
	if (commands[MOVE_DOWN]) CCharacter_Player::GetInstance()->moveDown();
	if (commands[MOVE_LEFT]) CCharacter_Player::GetInstance()->moveLeft();
	if (commands[MOVE_RIGHT]) CCharacter_Player::GetInstance()->moveRight();

	CCharacter_Player::GetInstance()->updatePosition(dt);
	//Weapon changing
	int CurrentWeapon = m_weapon->getWeapon();
	if (commands[PREVWEAP])CurrentWeapon--;
	if (commands[NEXTWEAP])CurrentWeapon++;
	m_weapon->setWeapon(CurrentWeapon);

	for (std::vector<CCharacter_Enemy *>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		
	}

	Vector3 initialCam;
	initialCam.Set(camera.position.x, camera.position.y, camera.position.z);
	Vector3 playerPos;
	playerPos.Set(CCharacter_Player::GetInstance()->getPosition().x, CCharacter_Player::GetInstance()->getPosition().y, 20);
	
	if (camera.position.Length() > 0 && ZoomIN)
	{
		camera.position += (playerPos - initialCam).Normalized() * (playerPos - initialCam).Length() * 2.0f * dt;
		camera.target += (playerPos - initialCam).Normalized() * (playerPos - initialCam).Length() * 2.0f * dt;
	}
	//Camera zoom in to player
	if (commands[ENTER] && !ZoomIN)
	{
		ZoomIN = true;
	}

	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;


}

void GameModel2D::setCommands(int command)
{
	if (command >= 0 && command < NUM_COMMANDS)
		commands[command] = true;
}

Mesh* GameModel2D::getTextMesh()
{
	return meshList[TEXT];
}

Mesh* GameModel2D::getBackgroundMesh()
{
	return meshList[BACKGROUND];
}

Mesh* GameModel2D::getCrosshairMesh()
{
	return meshList[CROSSHAIR];
}

void GameModel2D::getOffset(float& mapOffset_x, float& mapOffset_y)
{
	//mapOffset_x = m_mapOffset_x;
	//mapOffset_y = m_mapOffset_y;
}

TileMap* GameModel2D::getTileMap()
{
	return m_tileMap;
}

TileMap* GameModel2D::getRearTileMap()
{
	return m_ReartileMap;
}

Mesh* GameModel2D::getTileMesh()
{
	return meshList[TILE];
}

Mesh* GameModel2D::getFloorTileMesh()
{
	return meshList[TILEFLOOR];
}

PlayerWeapon* GameModel2D::getWeapon()
{
	return m_weapon;
}
Mesh* GameModel2D::getPlayerMesh(GEOMETRY_TYPE meshToTake)
{
	switch (meshToTake)
	{
	case PISTOL_IDLE:
		return meshList[PISTOL_IDLE];
		break;
	}
}
Mesh* GameModel2D::getWeaponMesh()
{
	switch (m_weapon->getWeapon())
	{
	case 0:
		m_weapon->setWeapon(PISTOL);
		break;
	case 1:
		m_weapon->setWeapon(SHOTGUN);
		break;
	case 2:
		m_weapon->setWeapon(RIFLE);
		break;
	}
	return weaponList[m_weapon->getWeapon()];
}

std::vector<CCharacter_Enemy*> GameModel2D::getEnemyList()
{
	return EnemyList;
}
Mesh* GameModel2D::getWeaponMesh()
{
	switch (m_weapon->getWeapon())
	{
	case 0:
		m_weapon->setWeapon(PISTOL);
		break;
	case 1:
		m_weapon->setWeapon(SHOTGUN);
		break;
	case 2:
		m_weapon->setWeapon(RIFLE);
		break;
	}
	return weaponList[m_weapon->getWeapon()];
}


std::vector<CCharacter_Enemy*> GameModel2D::getCollectiblesList()
{
	return CollectiblesList;
}

Mesh* GameModel2D::getMobsMesh()
{
	return meshList[MOBS];
}

int GameModel2D::getScore()
{
	return score;
}

int GameModel2D::getSpawnPointID()
{
	return SpawnPointID;
}

Vector3 GameModel2D::getNewPlayerPos()
{
	return newPlayerPos;
}

Vector3 GameModel2D::getNewExitPos()
{
	return newExitPos;
}

void GameModel2D::setNewPlayerPos(float x, float y, float z)
{
	if ( !newLevel )
	{
		newPlayerPos.Set(x,y,z);
		SpawnReady = true;
		newLevel = true;
	}
}

void GameModel2D::setNewExitPos(float x, float y, float z)
{
	newExitPos.Set(x,y,z);
}

int GameModel2D::getExitPointID()
{
	return ExitPointID;
}

int GameModel2D::getEnemySpawnID()
{
	return EnemySpawnID;
}

void GameModel2D::setNewEnemy(float x, float y, float z, int ID)
{
	for ( unsigned i = 0; i < EnemyList.size(); ++i)
	{
		if ( !EnemyList[i]->getActive() )
		{
			EnemyList[i]->setActive(true);
			EnemyList[i]->setPosition(x,y,z);
			EnemyList[i]->setID(ID);
			break;
		}
	}
}
