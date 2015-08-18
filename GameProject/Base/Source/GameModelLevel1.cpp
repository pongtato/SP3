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
	m_tileMap->LoadMap("Image//map.csv");

	m_ReartileMap = new TileMap();
	m_ReartileMap->Init(32, 32, 32, 32, 32);
	m_ReartileMap->LoadMap("Image//Maps//L1_L1.csv");

	player = new PlayerCharacter(Vector3(16, 3, 0));
}

void GameModelLevel1::Update(double dt)
{
	if (rand() % 100 < 1)
	{
		int pos = rand() % 2;
		Character *mob = new MouseCharacter(Vector3(1 + pos * 30, 2, 0), NULL, (pos ? -3 : 3), player);
		mobsList.push_back(mob);
	}

	GameModel2D::Update(dt);
}
