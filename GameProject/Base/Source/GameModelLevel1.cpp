#include "GameModelLevel1.h"

GameModelLevel1::GameModelLevel1()
{
}

GameModelLevel1::~GameModelLevel1()
{
}

void GameModelLevel1::Init()
{
	Model::Init();
	GameModel2D::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(32, 32, 32, 32, 32);
	m_tileMap->LoadMap("Image//Maps//L1_L2.csv");

	m_ReartileMap = new TileMap();
	m_ReartileMap->Init(32, 32, 32, 32, 32);
	m_ReartileMap->LoadMap("Image//Maps//L1_L1.csv");

	player = new PlayerCharacter(Vector3(newPlayerPos.x, newPlayerPos.y, 0));
}

void GameModelLevel1::Update(double dt)
{
	if ( SpawnReady )
	{
		player->InitPos(newPlayerPos.x - 0.5f,
			newPlayerPos.y - 0.25f,
			newPlayerPos.z);
		SpawnReady = false;
	}
	GameModel2D::Update(dt);
}
