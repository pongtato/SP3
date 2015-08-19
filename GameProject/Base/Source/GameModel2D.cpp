#include "GameModel2D.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

#include "MouseCharacter.h"

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

	commands = new bool[NUM_COMMANDS];
	for (int count = 0; count < NUM_COMMANDS; ++count)
		commands[count] = false;

	//m_mapOffset_x = 0;
	//m_mapOffset_y = 0;

	score = 0;
	ZoomIN = false;
}

void GameModel2D::Update(double dt)
{
	if (commands[MOVE_UP]) player->moveUp();
	if (commands[MOVE_DOWN]) player->moveDown();
	if (commands[MOVE_LEFT]) player->moveLeft();
	if (commands[MOVE_RIGHT]) player->moveRight();
	if (commands[JUMP]) player->jump();

	player->Update(dt, m_tileMap);

	//m_mapOffset_x = player->getPosition().x - (float)m_tileMap->getNumOfTilesWidth() / 2.f;
	//m_mapOffset_x = Math::Clamp(m_mapOffset_x, 0.f, (float)(m_tileMap->getMapWidth() - m_tileMap->getNumOfTilesWidth()));

	for (std::vector<Character *>::iterator it = mobsList.begin(); it != mobsList.end(); ++it)
	{
		(*it)->Update(dt, m_tileMap);
		if ((*it)->isActive())
		{
			if (CheckCollision(*it, player))
			{
				if (player->getVelocity().y < 0 && player->getPosition().y >(*it)->getPosition().y && !(*it)->isDead())
				{
					(*it)->SetDead();
					score++;
				}
			}
		}
	}

	/*Vector3 AssignVel;
	Vector3 tempVel;
	AssignVel.Set(camera.position.x,camera.position.y,0);
*/
	//Camera update
	//if ( (player->getPosition() - AssignVel).Length() > 3 && ZoomIN)
	//{
	//	if ( tempVel.Length() < 4)
	//	{
	//		tempVel += (player->getPosition() - AssignVel).Normalized() * (player->getPosition() - AssignVel).Length() * 0.5f * dt;
	//	}
	//}
	Vector3 initialCam;
	initialCam.Set(camera.position.x, camera.position.y, camera.position.z);
	Vector3 playerPos;
	playerPos.Set(player->getPosition().x, player->getPosition().y, 20);
	
	if (camera.position.Length() > 0 && ZoomIN)
	{
		camera.position += (playerPos - initialCam).Normalized() * (playerPos - initialCam).Length() * 0.5f * dt;
		camera.target += (playerPos - initialCam).Normalized() * (playerPos - initialCam).Length() * 0.5f * dt;
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

PlayerCharacter* GameModel2D::getPlayer()
{
	return player;
}

Mesh* GameModel2D::getPlayerMesh()
{
	return meshList[PLAYER];
}

std::vector<Character *> GameModel2D::getMobsList()
{
	return mobsList;
}

Mesh* GameModel2D::getMobsMesh()
{
	return meshList[MOBS];
}

int GameModel2D::getScore()
{
	return score;
}
