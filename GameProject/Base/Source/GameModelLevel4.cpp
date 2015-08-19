#include "GameModelLevel4.h"

GameModelLevel4::GameModelLevel4()
{
}

GameModelLevel4::~GameModelLevel4()
{
}

void GameModelLevel4::Init()
{
	Model::Init();
	GameModel2D::Init();

	m_tileMap = new TileMap();
	m_tileMap->Init(32, 32, 32, 32, 32);
	m_tileMap->LoadMap("Image//Maps//L4_L2.csv");

	m_ReartileMap = new TileMap();
	m_ReartileMap->Init(32, 32, 32, 32, 32);
	m_ReartileMap->LoadMap("Image//Maps//L4_L1.csv");

	player = new PlayerCharacter(Vector3(2, 2, 0));
	Character *mob = new Character_Guard(Vector3(16, 3, 0), NULL, -1, player);
}

void GameModelLevel4::Update(double dt)
{
	GameModel2D::Update(dt);
}
