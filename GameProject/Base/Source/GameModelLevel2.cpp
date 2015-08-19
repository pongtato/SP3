#include "GameModelLevel2.h"

GameModelLevel2::GameModelLevel2()
{
}

GameModelLevel2::~GameModelLevel2()
{
}

void GameModelLevel2::Init()
{
	Model::Init();
	GameModel2D::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(32, 32, 32, 32, 32);
	m_tileMap->LoadMap("Image//Maps//L2_L2.csv");

	m_ReartileMap = new TileMap();
	m_ReartileMap->Init(32, 32, 32, 32, 32);
	m_ReartileMap->LoadMap("Image//Maps//L2_L1.csv");

	player = new PlayerCharacter(Vector3(2, 2, 0));
}

void GameModelLevel2::Update(double dt)
{
	GameModel2D::Update(dt);
}
