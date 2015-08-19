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
	if (rand() % 100 < 1)
	{
		int pos = rand() % 2;
		Character *mob = new Character_Guard(Vector3(1 + pos * 30, 2, 0), NULL, (pos ? -3 : 3), player);
		GuardsList.push_back(mob);
	}

	if ( SpawnReady )
	{
		player->InitPos(newPlayerPos.x - 0.5f,
			newPlayerPos.y - 0.5f,
			newPlayerPos.z);
		SpawnReady = false;
	}

	std::cout << player->getPosition().x << "," << player->getPosition().y << std::endl;

	GameModel2D::Update(dt);
}
