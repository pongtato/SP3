#include "GameModel2D.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

#include "MouseCharacter.h"

const float m_worldHeight = 120;
const float m_worldWidth = 160;

void GameModel2D::Init()
{
	Model::Init();

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

	Vector3 AssignVel;
	Vector3 tempVel;
	AssignVel.Set(camera.position.x,camera.position.y,0);

	//Camera update
	if ( (player->getPosition() - AssignVel).Length() > 3 )
	{
		if ( tempVel.Length() < 4 )
		{
			tempVel += (player->getPosition() - AssignVel).Normalized() * (player->getPosition() - AssignVel).Length() * 0.5f * dt;
		}
	}
	camera.position.x += tempVel.x;
	camera.position.y += tempVel.y;
	camera.target += tempVel.x;
	camera.target.y += tempVel.y;

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
