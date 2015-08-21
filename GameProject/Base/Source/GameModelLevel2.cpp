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

	CCharacter_Player::GetInstance()->Init(newPlayerPos.x - 0.5f,
			newPlayerPos.y - 0.25f,
			newPlayerPos.z,1,1,100,1,5);
}

void GameModelLevel2::Update(double dt)
{
	if ( SpawnReady )
	{
		CCharacter_Player::GetInstance()->Init(newPlayerPos.x,
			newPlayerPos.y,
			newPlayerPos.z,1,1,100,1,5);
		SpawnReady = false;
	}
	GameModel2D::Update(dt);
}
